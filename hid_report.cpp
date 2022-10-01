#include "hid_report.h"

#include "HIDTypes.h"
#include <cstring>







const uint8_t hid_report_descriptor[] = {
USAGE_PAGE(1),      0x01,                    // Usage Page (Generic Desktop)        0
USAGE(1),           0x06,                    // Usage (Keyboard)                    2
COLLECTION(1),      0x01,                    // Collection (Application)            4

REPORT_ID(1),       KEYBOARD_KEYS_ID,        //  Report ID (KEYBOARD_KEYS_ID)                      6
// modifier keys
REPORT_COUNT(1),    0x08,                    //  Report Count (8)                   8
REPORT_SIZE(1),     0x01,                    //  Report Size (1)                    10
LOGICAL_MINIMUM(1), 0x00,                    //  Logical Minimum (0)                12
LOGICAL_MAXIMUM(1), 0x01,                    //  Logical Maximum (1)                14
USAGE_PAGE(1),      0x07,                    //  Usage Page (Keyboard)              16
USAGE_MINIMUM(1),   0xe0,                    //  Usage Minimum (224)                18
USAGE_MAXIMUM(1),   0xe7,                    //  Usage Maximum (231)                20
HIDINPUT(1),        0x02,                    //  Input (Data,Var,Abs)               22
// 6 simultaneous keys
REPORT_COUNT(1),    0x06,                    //  Report Count (6)                   24
REPORT_SIZE(1),     0x08,                    //  Report Size (8)                    26
LOGICAL_MINIMUM(1), 0x00,                    //  Logical Minimum (0)                28
LOGICAL_MAXIMUM(2), 0xff, 0x00,              //  Logical Maximum (255)              30
USAGE_PAGE(1),      0x07,                    //  Usage Page (Keyboard)              33
USAGE_MINIMUM(1),   0x00,                    //  Usage Minimum (0)                  35
USAGE_MAXIMUM(2),   0xff, 0x00,              //  Usage Maximum (255)                37
HIDINPUT(1),        0x00,                    //  Input (Data,Arr,Abs)               40
// keyboard lights
REPORT_ID(1),       KEYBOARD_LIGHTS_ID,      //  Report ID (KEYBOARD_LIGHTS_ID)                     42
USAGE_PAGE(1),      0x08,                    //  Usage Page (LEDs)                  44
REPORT_COUNT(1),    0x05,                    //  Report Count (5)                   46
REPORT_SIZE(1),     0x01,                    //  Report Size (1)                    48
LOGICAL_MINIMUM(1), 0x00,                    //  Logical Minimum (0)                50
LOGICAL_MAXIMUM(1), 0x01,                    //  Logical Maximum (1)                52
USAGE_MINIMUM(1),   0x01,                    //  Usage Minimum (1)                  54
USAGE_MAXIMUM(1),   0x05,                    //  Usage Maximum (5)                  56
HIDOUTPUT(1),       0x02,                    //  Output (Data,Var,Abs)              58
REPORT_COUNT(1),    0x01,                    //  Report Count (1)                   60
REPORT_SIZE(1),     0x03,                    //  Report Size (3)                    62
HIDOUTPUT(1),       0x01,                    //  Output (Cnst,Arr,Abs)              64
END_COLLECTION(0),                           // End Collection                      66



USAGE_PAGE(1),      0x0C,                    // USAGE_PAGE (Consumer)
USAGE(1),           0x01,                    // USAGE (Consumer Control)
COLLECTION(1),      0x01,                    // COLLECTION (Application)
REPORT_ID(1),       MEDIA_ID,           //   REPORT_ID (MEDIA_KEYS_IDj)
USAGE_PAGE(1),      0x0C,                    //   USAGE_PAGE (Consumer)
LOGICAL_MINIMUM(1), 0x00,                    //   LOGICAL_MINIMUM (0)
LOGICAL_MAXIMUM(1), 0x01,                    //   LOGICAL_MAXIMUM (1)
REPORT_SIZE(1),     0x01,                    //   REPORT_SIZE (1)
REPORT_COUNT(1),    0x10,                    //   REPORT_COUNT (16)
USAGE(1),           0xB5,                    //   USAGE (Scan Next Track)     ; bit 0: 1
USAGE(1),           0xB6,                    //   USAGE (Scan Previous Track) ; bit 1: 2
USAGE(1),           0xB7,                    //   USAGE (Stop)                ; bit 2: 4
USAGE(1),           0xCD,                    //   USAGE (Play/Pause)          ; bit 3: 8
USAGE(1),           0xE2,                    //   USAGE (Mute)                ; bit 4: 16
USAGE(1),           0xE9,                    //   USAGE (Volume Increment)    ; bit 5: 32
USAGE(1),           0xEA,                    //   USAGE (Volume Decrement)    ; bit 6: 64
USAGE(2),           0x23, 0x02,              //   Usage (WWW Home)            ; bit 7: 128
USAGE(2),           0x94, 0x01,              //   Usage (My Computer) ; bit 0: 1
USAGE(2),           0x92, 0x01,              //   Usage (Calculator)  ; bit 1: 2
USAGE(2),           0x2A, 0x02,              //   Usage (WWW fav)     ; bit 2: 4
USAGE(2),           0x21, 0x02,              //   Usage (WWW search)  ; bit 3: 8
USAGE(2),           0x26, 0x02,              //   Usage (WWW stop)    ; bit 4: 16
USAGE(2),           0x24, 0x02,              //   Usage (WWW back)    ; bit 5: 32
USAGE(2),           0x83, 0x01,              //   Usage (Media sel)   ; bit 6: 64
USAGE(2),           0x8A, 0x01,              //   Usage (Mail)        ; bit 7: 128
HIDINPUT(1),        0x02,                    //   INPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
END_COLLECTION(0),                            // END_COLLECTION


USAGE_PAGE(1),      0x01,                    // Usage Page (Generic Desktop)        67
USAGE(1),           0x02,                    // Usage (Mouse)                       69
COLLECTION(1),      0x01,                    // Collection (Application)            71
REPORT_ID(1),       MOUSE_ID,                //  Report ID (MOUSE_ID)                      73
USAGE(1),           0x01,                    //  Usage (Pointer)                    75
COLLECTION(1),      0x00,                    //  Collection (Physical)              77
USAGE_PAGE(1),      0x09,                    //   Usage Page (Button)               79
USAGE_MINIMUM(1),   0x01,                    //   Usage Minimum (1)                 81
USAGE_MAXIMUM(1),   0x10,                    //   Usage Maximum (16)                83
LOGICAL_MINIMUM(1), 0x00,                    //   Logical Minimum (0)               85
LOGICAL_MAXIMUM(1), 0x01,                    //   Logical Maximum (1)               87
REPORT_COUNT(1),    0x10,                    //   Report Count (16)                 89
REPORT_SIZE(1),     0x01,                    //   Report Size (1)                   91
HIDINPUT(1),        0x02,                    //   Input (Data,Var,Abs)              93
USAGE_PAGE(1),      0x01,                    //   Usage Page (Generic Desktop)      95
LOGICAL_MINIMUM(2), 0x01, 0xf8,              //   Logical Minimum (-2047)           97
LOGICAL_MAXIMUM(2), 0xff, 0x07,              //   Logical Maximum (2047)            100
REPORT_SIZE(1),     0x0c,                    //   Report Size (12)                  103
REPORT_COUNT(1),    0x02,                    //   Report Count (2)                  105
USAGE(1),           0x30,                    //   Usage (X)                         107
USAGE(1),           0x31,                    //   Usage (Y)                         109
HIDINPUT(1),        0x06,                    //   Input (Data,Var,Rel)              111
LOGICAL_MINIMUM(1), 0x81,                    //   Logical Minimum (-127)            113
LOGICAL_MAXIMUM(1), 0x7f,                    //   Logical Maximum (127)             115
REPORT_SIZE(1),     0x08,                    //   Report Size (8)                   117
REPORT_COUNT(1),    0x01,                    //   Report Count (1)                  119
USAGE(1),           0x38,                    //   Usage (Wheel)                     121
HIDINPUT(1),        0x06,                    //   Input (Data,Var,Rel)              123
USAGE_PAGE(1),      0x0c,                    //   Usage Page (Consumer Devices)     125
USAGE(2),           0x38, 0x02,              //   Usage (AC Pan)                    127
REPORT_COUNT(1),    0x01,                    //   Report Count (1)                  130
HIDINPUT(1),        0x06,                    //   Input (Data,Var,Rel)              132
END_COLLECTION(0),                           //  End Collection                     134
END_COLLECTION(0),                           // End Collection                      135


};
const uint32_t hid_report_descriptor_size = sizeof(hid_report_descriptor);




uint8_t* pack_mouse_report(
  uint16_t buttons,
  int16_t x, int16_t y,
  int8_t wheel_v, int8_t wheel_h,
  uint8_t* buf
){
  //pack the X and Y axes into a 32b uint from 12b ints
  uint32_t xy = (x & 0x0fff) | (((uint32_t) (y & 0x0fff)) <<12);

  buf[0] = buttons & 0xff;
  buf[1] = (buttons >> 8) & 0xff;
  buf[2] = xy & 0xff;
  buf[3] = ((xy >> 8) & 0xff);
  buf[4] = ((xy >> 16) & 0xff);
  buf[5] = wheel_v;
  buf[6] = wheel_h;
  return buf;
}


uint8_t* pack_keyboard_report(
  uint8_t mod,
  const uint8_t* scan_codes,    // only 6 scan codes
  uint8_t* buf
){

  buf[0] = mod;
  memcpy(&buf[1], scan_codes, 6);
  return buf;
}



