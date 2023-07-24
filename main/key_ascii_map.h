#ifndef KEY_ASCII_MAP_H
#define KEY_ASCII_MAP_H
#include <stdint.h>

//flag to indicate that the character is only accessible with Shift key
#define KEY_ACSII_MAP_SHIFT 0x80

// scan codes for modifier keys implemented as HID dynamic flags
#define KM_L_CTRL           (1<<0)
#define KM_L_SHIFT          (1<<1)
#define KM_L_ALT            (1<<2)
#define KM_L_GUI            (1<<3)
#define KM_R_CTRL           (1<<4)
#define KM_R_SHIFT          (1<<5)
#define KM_R_ALT            (1<<6)
#define KM_R_GUI            (1<<7)

#define KC_A                (0x04)
#define KC_ALPHA(c)         (KC_A + ((c)-'a'))

#define KC_0                (0x27)
#define KC_1                (0x1E)
#define KC_2                (0x1F)
#define KC_3                (0x20)
#define KC_4                (0x21)
#define KC_5                (0x22)
#define KC_6                (0x23)
#define KC_7                (0x24)
#define KC_8                (0x25)
#define KC_9                (0x26)

#define KC_ENTER            (0x28)
#define KC_BACKSPACE        (0x2A)
#define KC_DELETE           (0x4C)
#define KC_ESCAPE           (0x29)

#define KC_PRINTSCR         (0x46)
#define KC_SCROLLLOCK       (0x47)
#define KC_PAUSE            (0x48)
#define KC_INSERT           (0x49)

#define KC_HOME             (0x4A)
#define KC_END              (0x4D)
#define KC_PAGE_UP          (0x4B)
#define KC_PAGE_DOWN        (0x4E)

#define KC_RIGHT            (0x4F)
#define KC_LEFT             (0x50)
#define KC_DOWN             (0x51)
#define KC_UP               (0x52)

#define KC_F1               (0x3A)
#define KC_F13              (0x68)
#define KC_FN(num)          (((num)<13)?(((num)-1)+KC_F1):(((num)-13)+KC_F13))

#define KC_EXECUTE          (0x74)
#define KC_HELP             (0x75)
#define KC_MENU             (0x76)
#define KC_SELECT           (0x77)
#define KC_STOP             (0x78)
#define KC_AGAIN            (0x79)
#define KC_UNDO             (0x7A)

#define KC_CUT              (0x7B)
#define KC_COPY             (0x7C)
#define KC_PASTE            (0x7D)

#define KC_FIND             (0x7E)

#define KC_MUTE             (0x7F)
#define KC_VOL_UP           (0x80)
#define KC_VOL_DOWN         (0x81)


extern const uint8_t        key_ascii_map[128];
#define KC_LOOKUP(c)        (key_ascii_map[0x7F & (c)])
#define KC_CHAR(c)          ((~KEY_ACSII_MAP_SHIFT) & KC_LOOKUP(c))
#define KC_SHIFT(c)         (0 != (KEY_ACSII_MAP_SHIFT & KC_LOOKUP(c)))


// mouse buttons too while we're at it
#define MC_L (0x01)
#define MC_M (0x04)
#define MC_R (0x02)

#endif // KEY_ASCII_MAP_H
