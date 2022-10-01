#ifndef CHORDTOOLS_H
#define CHORDTOOLS_H

#include <stdint.h>
#include <stddef.h>
#include "keyscan.h"
#include "key_ascii_map.h"

#include "ble_gyromouse.h"

// store each BLE report separately
typedef struct  {
  uint8_t modifiers;
  uint8_t keys[6];
} keyreport_t;


enum macro_table_entry_type{
  KEYREPORT, // a full keyreport with six keys
  MEDIAREPORT, // a full media button report
  MOUSEREPORT,  // a full mouse report
  STRING      // a null-terminated string to generate key reports from
};


typedef struct {
  const macro_table_entry_type type;
  union{
    const keyreport_t* key;
    const char* string;
    //mediareport_t* media;
    //mousereport_t* mouse;
  };
} macro_table_entry_t;


// for each chord, record how many reports need to be sent
typedef struct  {
  chord_t chord;  // physical key
  const char* name; // human readable name for printing keymaps
  size_t n_reports;  // number of reports to send for the chord
  const macro_table_entry_t* macro;    // the array of reports to send
} chordmacro_t;


void compare_chords(void* cxt, chord_t old_chord, chord_t new_chord);
chord_t released_chord(chord_t old_chord, chord_t new_chord);
void send_string_as_keyreps(BleGyroMouse* keyb, const char* str);
void send_macro(BleGyroMouse* keyb, const chordmacro_t* macro);
const chordmacro_t* search_chord_table(
  chord_t chord,
  const chordmacro_t* table,
  size_t table_size);


enum FingerPos{
    O = 0,    //Open
    E = 1,    //Extended
    M = 2,    //Middle
    C = 4,    //Closed / Curled
    A = 7     //All (mask)
};


// Syntax sugar to describe finger positions
//#define POS(f) ( (f) ? (1<<(f-1)) : 0 )
#define CHORD(f1, f2, f3, f4) ((f1)<<3 | (f2)<<6 | (f3)<<9 | (f4)<<12)
#define CHORD_MOUSE_L (0x04)
#define CHORD_MOUSE_M (0x02)
#define CHORD_MOUSE_R (0x01)

// convenience functions for putting a keymap together
#define KEYREP(mod, ...) (keyreport_t){.modifiers=mod, .keys={__VA_ARGS__}}
#define KEY_MACRO(mod, ...)  {.type=KEYREPORT, .key = (keyreport_t[]) {KEYREP(mod,__VA_ARGS__)}}


constexpr macro_table_entry_t str_macro(const char* str){
  return (macro_table_entry_t){.type=STRING, .string=str};
}

// in C++11, you can't get around needing to actually have arrays.
//   No combination of constexpr will let you avoid
//   preprocessor macros when you're building a pointer-linked struct
/*

constexpr macro_table_entry_t key_macro(const keyreport_t* keyrep){
  return (macro_table_entry_t){.type=KEYREPORT, .key = keyrep};
}
#define KEY_MACRO(mod, keys) key_macro( (keyreport_t[]){KEYREP(mod,keys)})

*/
// the result still requires preprocessor but now the compiler knows less





template<class T, size_t N>
constexpr size_t count(T (&)[N]) { return N; }


// helper function to avoid manually counting the number of array entries
template<size_t N>
constexpr chordmacro_t make_macro(
  chord_t chord,
  const macro_table_entry_t (& macro)[N],  // static array counting trick
  const char* name = ""
){
  return (chordmacro_t) {
    .chord = chord,
    .name = name,
    .n_reports = N,
    .macro = macro
  };
}
// C++11 requires all manner of type decorations for
//    brace enclosed initialisers, hide them in a macro.
#define MACRO(chord, name, table...) make_macro(chord,(macro_table_entry_t[]){table}, name)


void print_macro_table(
  const chordmacro_t* table,
  size_t table_len,
  void (*callback)(const char*)
  );



#endif //CHORDTOOLS_H