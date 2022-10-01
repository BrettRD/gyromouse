
/*
 * The PCF8574 has a weak pull up resistor on all de-asserted pins
 * and a strong pull-down on all asserted pins
 * Drive a column low to read matrix switches on each row by reading a single word
 * Drive all columns low to allow triggering of interrupt on a single keypress.
 * This lib uses a context pointer to interact with external libraries
 */

//#include "Arduino.h"

#include "keyscan.h"
#include <bitset>         // std::bitset

const int n_cols = 3;
const int n_rows = 5;
const int col_pins[n_cols] = {7,4,1};
const int row_pins[n_rows] = {6,5,2,3,0};

//const int n_cols = 5;
//const int n_rows = 3;
//const int col_pins[n_cols] = {6,5,2,3,0};
//const int row_pins[n_rows] = {7,4,1};


bool keyb_int_valid(chord_t chord){
  for(int row=0; row<n_rows; row++){
    chord_t mask = ((1<<n_cols)-1) << (row*n_cols);
    chord_t row_state = mask & chord;
    if( __builtin_popcount(row_state) > 1){
      return false;
    }
  }
  return true;
}


void keyscan(void* cxt, chord_t* chord){
  *chord = 0;
  for(int col=0; col<n_cols; col++){
    uint8_t row_data = 0;
    PCF8574_write_io(cxt, ~(uint8_t)(1<<col_pins[col]));
    PCF8574_read_io(cxt, &row_data);
    //Serial.print("col ");
    //Serial.print(col);
    //Serial.print(" data ");
    
    for(int row=0; row<n_rows; row++){
      uint8_t button_bit_num = row_pins[row];
      chord_t btn_val = ((~row_data >> button_bit_num) & 0x01);
      //Serial.print(btn_val);
      uint16_t chord_bit_num = col + (row*n_cols);
      *chord |= btn_val << (chord_bit_num);
    }
    //Serial.println(' ');
  }
  
  
  // set the columns to pull down so any button will change a row state
  if(keyb_int_valid(*chord)){
    uint8_t col_rest = 0xff;
    for(int col=0; col<n_cols; col++){
      col_rest &= ~(uint8_t)(1<<col_pins[col]);
    }
    PCF8574_write_io(cxt, col_rest);
  }


  return;
}
