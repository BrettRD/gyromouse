#ifndef HID_REPORT_H
#define HID_REPORT_H


#include <stdint.h>
#include <stddef.h>


#define KEYBOARD_KEYS_ID 0x01
#define KEYBOARD_LIGHTS_ID 0x02
#define MEDIA_ID 0x03
#define MOUSE_ID 0x04
#define N_REPORTS 4

extern const uint8_t hid_report_descriptor[];
extern const uint32_t hid_report_descriptor_size;

const size_t keyboard_report_len = 7;
const size_t mouse_report_len = 7;

const int32_t mouse_trans_max = 2047;
const int32_t mouse_wheel_max = 127;


// Packs the mouse HID report.
// Make sure to update the HID table if you change this
// note that x and y are only 12b integers
uint8_t* pack_mouse_report(
  uint16_t buttons,
  int16_t x, int16_t y,
  int8_t wheel_v, int8_t wheel_h,
  uint8_t* buf
);


uint8_t* pack_keyboard_report(
  uint8_t mod,
  const uint8_t* scan_codes,    // only 6 scan codes
  uint8_t* buf
);


#endif // HID_REPORT_H