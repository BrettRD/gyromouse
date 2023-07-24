
#include "Wire.h"

#include "keyscan.h"
#include "pcf8574_wire.h"
#include "trackball.hpp"
#include <MPU9250_asukiaaa.h>
#include "ble_gyromouse.h"

#include "chordtools.h"
#include "chordmap.h"

const int key_scan_int_pin = 13;
const uint8_t key_scan_i2c_addr = 0x38; //  PCF8574A
// const uint8_t key_scan_i2c_addr = 0x20; //  PCF8574 stripboard,

MPU9250_asukiaaa mpu;
BleGyroMouse bleMouse;

i2c_shim tb_i2c_shim((void*) &Wire);
Trackball trackball(&tb_i2c_shim);
// context pointer to feed the keyscan system
wire_cxt pcf_cxt = {&Wire, key_scan_i2c_addr};


void scan_i2c();
float dps_curve(float dps);


//accumulators for the mouse
float mouse_x_accu, mouse_y_accu = 0;
float sensitivity = 30.0 / 1000000;

// XXX really need a proper motion filter (madgwick?) to recover gyro bias
float gyro_bias[3] = {-0.3,-1.8,0.3};

float gyro_vectors[9] = {
   0.5,   0, 0.8,
     0,  -1,   0,
     0,   0,   0};


// remember the last chord so we can sleep between keyboard interrupts
chord_t chord = 0;
// remember the chord before that so we can see which chord was released
chord_t old_chord = 0;


// remember the last chord release time so we can debounce/inhibit
uint32_t chord_timer = 0;
// inhibit new chords for this length of time after chord activation
uint32_t chord_inhibit_time = 100*1000;
// compensate non-uniform sampling of the gyro
uint32_t gyro_timer = 0;

// temporary variables 
float Gxyz[3];  //gyro raw data
uint8_t buf[mouse_report_len];  // buffer to carry the mouse BLE data

uint8_t tb_r,tb_g,tb_b,tb_w;  // trackball colours

void print_table_cb(const char* str){
  //Serial.print(str);
}

void setup()
{
  
  // Wire.begin(4,15); // SDA, SCL //stripboard
  Wire.begin(9,10); // SDA, SCL // proto0

  //Serial.begin(38400);
  delay(2000);
  print_macro_table(macro_map, macro_map_size, print_table_cb);

  // diagnostics, check the sensors exist
  scan_i2c();


  pinMode(key_scan_int_pin, INPUT_PULLUP);  //keypad interrupt pin

  
  mpu.setWire(&Wire);
  mpu.beginAccel();
  mpu.beginGyro(GYRO_FULL_SCALE_2000_DPS);

  keyscan(&pcf_cxt, &chord);

  if(trackball.init()){
    //Serial.println("Trackball OK");
  } else {
    //Serial.println("Trackball Failed");
  }


  //Serial.println("Starting BLE...");
  bleMouse.begin();
  delay(1000);
  //Serial.println("Start");


}

void loop()
{

  // capture IMU data
  uint32_t gyro_time = micros();
  uint32_t gyro_dt = gyro_time - gyro_timer;
  gyro_timer = gyro_time;

  uint8_t err = mpu.gyroUpdate();
  Gxyz[0]=mpu.gyroX();
  Gxyz[1]=mpu.gyroY();
  Gxyz[2]=mpu.gyroZ();


  Trackball::State tb_state;
  tb_state = trackball.read();
  tb_r += tb_state.up;
  tb_r -= tb_state.down;
  tb_g += tb_state.left;
  tb_g -= tb_state.right;
  tb_w = tb_state.sw_pressed ? 255 : 0;
  trackball.set_rgbw(tb_r, tb_g, tb_b, tb_w);

  int8_t tb_x = tb_state.right - tb_state.left;
  int8_t tb_y = tb_state.up - tb_state.down;


  // the keypad will set the int pin on pin5 from chord 0,
  //    but we need to poll from other states
  if(!keyb_int_valid(chord)){
    //Serial.println("chord poll");
  }

  // if the interrupt line won't indicate release, we need to actively scan
  // otherwise, if the interrupt line is triggered there's a new chord state to read
  if(!keyb_int_valid(chord) || (LOW == digitalRead(key_scan_int_pin))){
    keyscan(&pcf_cxt, &chord);
    // report non-zero chords
    if((chord!=0)&&(old_chord!=chord)){
      //Serial.print("chord: ");
      //Serial.println(chord);
    }

    if(bleMouse.isConnected()) {
      // keypresses happen on chord release (consider a direct-entry mode for gaming)
      // partial releases count
      chord_t ch_rel = released_chord(old_chord, chord);
      // inhibit the acceptance of new chords immediately following other chords
      uint32_t timestamp = micros();
      if((ch_rel != 0) && (timestamp > (chord_timer+chord_inhibit_time))){
        chord_timer = timestamp;
        // the chord was valid, and not part of a larger chord release
        // look up the macro associated with the chord
        const chordmacro_t* macro = search_chord_table(
          ch_rel,
          macro_map,
          macro_map_size
        );
        // the pointer to the macro will be NULL if the chord was not found
        if(macro){
          // unpack the macro into BLE packets and send them
          send_macro(&bleMouse, macro);
        }
      }
    }
  }




  if(bleMouse.isConnected()) {
    // an arbitrary reserved chord used in direct-entry mode unmasks the gyro

    
    if(chord == CHORD(E,O,E,M)){
      // mouse is activated, integrate the angle

      float raw_rates[3] = {
        (Gxyz[0] - gyro_bias[0]),
        (Gxyz[1] - gyro_bias[1]),
        (Gxyz[2] - gyro_bias[2])
      };
      
      float aligned_rates[3] = {
        (Gxyz[0] * gyro_vectors[0]) + (Gxyz[1] * gyro_vectors[1]) + (Gxyz[2] * gyro_vectors[2]),
        (Gxyz[0] * gyro_vectors[3]) + (Gxyz[1] * gyro_vectors[4]) + (Gxyz[2] * gyro_vectors[5]),
        (Gxyz[0] * gyro_vectors[6]) + (Gxyz[1] * gyro_vectors[7]) + (Gxyz[2] * gyro_vectors[9])
      };

      mouse_x_accu += dps_curve(aligned_rates[0], gyro_dt);
      mouse_y_accu += dps_curve(aligned_rates[1], gyro_dt);
      
    }

    if(
      ((old_chord^chord) & mouse_mask) ||   // if we need to click
      (abs(mouse_x_accu) >= 1.0) ||          // we need to move in X
      (abs(mouse_y_accu) >= 1.0) ||          // we need to move in Y
      (abs(tb_x) > 0) ||                    // we need to scroll the wheel
      (abs(tb_y) > 0)                       // we need to scroll the wheel
    ){
      // write the gyro accumulator (float) to the right number format
      int16_t x_motion = mouse_x_accu;
      int16_t y_motion = mouse_y_accu;

      //clamp the mouse motion to values that can be carried by BLE
      if(mouse_x_accu > mouse_trans_max){
        x_motion = mouse_trans_max;
      } else if (mouse_x_accu < -mouse_trans_max){
        x_motion = -mouse_trans_max;
      }

      if(mouse_y_accu > mouse_trans_max){
        y_motion = mouse_trans_max;
      } else if (mouse_y_accu < -mouse_trans_max){
        y_motion = -mouse_trans_max;
      }

      // clamp the wheel values

      // we have the information we need to send the report
      bleMouse.send_mouse_report(
        pack_mouse_report(
          mouse_buttons(chord),   // convert physical buttons to mouse buttons
          x_motion, y_motion,
          tb_y, tb_x,
          buf
        )
      );

      // deduct the amount we moved from the integrator
      mouse_x_accu -= x_motion;
      mouse_y_accu -= y_motion;
    }
  }




  // update the old_chord state so we can remember what the chord was
  //    before it was activated by release
  old_chord=chord;

}






float dps_curve(float dps, uint32_t dt_us){
  // gyro mouse needs to be strictly linear,
  // just deal with non-uniform sampling and sensitivity
  return dps * sensitivity * dt_us; 
}


void scan_i2c()
{
  byte error, address;
  int nDevices;

  //Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      //Serial.print("I2C device found at address 0x");
      if (address<16)
        //Serial.print("0");
      //Serial.print(address,HEX);
      //Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      //Serial.print("Unknown error at address 0x");
      if (address<16){
        //Serial.print("0");
      }
      //Serial.println(address,HEX);
    }
  }
  if (nDevices == 0){
    //Serial.println("No I2C devices found\n");
  }
  else{
    //Serial.println("done\n");
  }
}
