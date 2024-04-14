
#include "chordmap.h"



// individual macros can have arbitrary combinations of hid report types
const macro_table_entry_t konami_code[] = {
  KEY_MACRO(0,KC_UP),
  KEY_MACRO(0,0),
  KEY_MACRO(0,KC_UP),
  KEY_MACRO(0,KC_DOWN),
  KEY_MACRO(0,0),
  KEY_MACRO(0,KC_DOWN),
  KEY_MACRO(0,KC_LEFT),
  KEY_MACRO(0,KC_RIGHT),
  KEY_MACRO(0,KC_LEFT),
  KEY_MACRO(0,KC_RIGHT),
  str_macro("BA"),
  KEY_MACRO(0,0)
}; 



// mouse actions are considered part of the keymap
uint8_t mouse_buttons(chord_t chord){
  return  ((chord & CHORD_MOUSE_L) ? MC_L : 0) |
        //((chord & CHORD_MOUSE_M) ? MC_M : 0) |  // using trackball for middle mouse
          ((chord & CHORD_MOUSE_R) ? MC_R : 0);
}


// Chord table transcribed from Alex Bravo's backspice layout for the Twiddler3
//  https://github.com/AlexBravo/Twiddler
const chordmacro_t macro_map[] = {

  //home row
  MACRO( CHORD(C,O,O,O), "BCKSP", KEY_MACRO(0,KC_BACKSPACE), KEY_MACRO(0,0)),
  MACRO( CHORD(M,O,O,O), "SPC",   str_macro(" ")),
  MACRO( CHORD(E,O,O,O), "s",     str_macro("s")),

  // page 0
  MACRO( CHORD(O,C,O,O), "i",     str_macro("i")),
  MACRO( CHORD(O,M,O,O), "e",     str_macro("e")),
  MACRO( CHORD(O,E,O,O), "o",     str_macro("o")),

  MACRO( CHORD(O,C,C,O), "in",    str_macro("in")),
  MACRO( CHORD(O,M,M,O), "et",    str_macro("et")),
  MACRO( CHORD(O,E,E,O), "or",    str_macro("or")),

  MACRO( CHORD(O,O,C,O), "n",     str_macro("n")),
  MACRO( CHORD(O,O,M,O), "t",     str_macro("t")),
  MACRO( CHORD(O,O,E,O), "r",     str_macro("r")),

  MACRO( CHORD(O,O,C,C), "an",    str_macro("an")),
  MACRO( CHORD(O,O,M,M), "th",    str_macro("th")),
  MACRO( CHORD(O,O,E,E), "FND",   KEY_MACRO(0,KC_FIND), KEY_MACRO(0,0)),

  MACRO( CHORD(O,O,O,C), "a",     str_macro("a")),
  MACRO( CHORD(O,O,O,M), "h",     str_macro("h")),
  MACRO( CHORD(O,O,O,E), "TAB",   str_macro("\t")),

  // page 1
  MACRO( CHORD(C,C,O,O), "3",     str_macro("3")),
  MACRO( CHORD(C,M,O,O), "UP",    KEY_MACRO(0,KC_UP), KEY_MACRO(0,0)),
  MACRO( CHORD(C,E,O,O), "6",     str_macro("6")),

  MACRO( CHORD(C,C,C,O), "CPY",   KEY_MACRO(0,KC_COPY), KEY_MACRO(0,0)),
  MACRO( CHORD(C,M,M,O), "0",     str_macro("0")),
  MACRO( CHORD(C,E,E,O), "9",     str_macro("9")),

  MACRO( CHORD(C,O,C,O), "4",     str_macro("4")),
  MACRO( CHORD(C,O,M,O), "DOWN",  KEY_MACRO(0,KC_DOWN), KEY_MACRO(0,0)),
  MACRO( CHORD(C,O,E,O), "7",     str_macro("7")),

  MACRO( CHORD(C,O,C,C), "8",     str_macro("8")),
  MACRO( CHORD(C,O,M,M), "1",     str_macro("1")),
//MACRO( CHORD(C,O,E,E), "",      str_macro("")),

  MACRO( CHORD(C,O,O,C), "5",     str_macro("5")),
  MACRO( CHORD(C,O,O,M), "2",     str_macro("2")),
  MACRO( CHORD(C,O,O,E), "ESC",   KEY_MACRO(0,KC_ESCAPE), KEY_MACRO(0,0)),

  // page 2
  MACRO( CHORD(M,C,O,O), "c",     str_macro("c")),
  MACRO( CHORD(M,M,O,O), "LEFT",  KEY_MACRO(0,KC_LEFT), KEY_MACRO(0,0)),
  MACRO( CHORD(M,E,O,O), "RIGHT", KEY_MACRO(0,KC_RIGHT), KEY_MACRO(0,0)),

  MACRO( CHORD(M,C,C,O), ",",     str_macro(",")),
  MACRO( CHORD(M,M,M,O), "DEL",   KEY_MACRO(0,KC_DELETE), KEY_MACRO(0,0)),
  MACRO( CHORD(M,E,E,O), "ou",    str_macro("ou")),

  MACRO( CHORD(M,O,C,O), "d",     str_macro("d")),
  MACRO( CHORD(M,O,M,O), "l",     str_macro("l")),
  MACRO( CHORD(M,O,E,O), "u",     str_macro("u")),

  MACRO( CHORD(M,O,C,C), "and",   str_macro("and")),
  MACRO( CHORD(M,O,M,M), "ENTER", KEY_MACRO(0,KC_ENTER), KEY_MACRO(0,0)),
//MACRO( CHORD(M,O,E,E), "",      str_macro("")),

  MACRO( CHORD(M,O,O,C), "f",     str_macro("f")),
  MACRO( CHORD(M,O,O,M), "m",     str_macro("m")),
  MACRO( CHORD(M,O,O,E), "_",     str_macro("_")),

  // page 3
  MACRO( CHORD(E,C,O,O), "is",    str_macro("is")),
  MACRO( CHORD(E,M,O,O), "es",    str_macro("es")),
//MACRO( CHORD(E,C,C,O), "",      str_macro("")),
  MACRO( CHORD(E,M,M,O), "PUP",   KEY_MACRO(0,KC_PAGE_UP), KEY_MACRO(0,0)),
  MACRO( CHORD(E,E,E,O), ";",     str_macro(";")),

  MACRO( CHORD(E,O,C,O), "{",     str_macro("{")),
  MACRO( CHORD(E,O,M,O), "st",    str_macro("st")),
  MACRO( CHORD(E,O,E,O), "}",     str_macro("}")),

  MACRO( CHORD(E,O,C,C), "(",     str_macro("(")),
  MACRO( CHORD(E,O,M,M), ")",     str_macro(")")),
//MACRO( CHORD(E,O,E,E), "",      str_macro("")),

  MACRO( CHORD(E,O,O,C), "as",    str_macro("as")),
  MACRO( CHORD(E,O,O,M), "w",     str_macro("w")),
  MACRO( CHORD(E,O,O,E), "`",     str_macro("`")),

  // page 4
  MACRO( CHORD(O,C,C,O), "in",    str_macro("in")),
  MACRO( CHORD(O,C,M,O), "it",    str_macro("it")),
  MACRO( CHORD(O,C,E,O), "+",     str_macro("+")),

  MACRO( CHORD(O,C,C,C), "ing",   str_macro("ing")),
  MACRO( CHORD(O,C,M,M), "k",     str_macro("k")),
//MACRO( CHORD(O,C,E,E), "",      str_macro("")),

  MACRO( CHORD(O,C,C,C), "g",     str_macro("g")),
  MACRO( CHORD(O,C,M,M), "y",     str_macro("y")),
  MACRO( CHORD(O,C,E,E), "^",     str_macro("^")),

  // page 5
  MACRO( CHORD(C,C,C,O), "CPY",   KEY_MACRO(0,KC_COPY), KEY_MACRO(0,0)),
  MACRO( CHORD(C,C,M,O), "PST",   KEY_MACRO(0,KC_PASTE), KEY_MACRO(0,0)),
  MACRO( CHORD(C,C,E,O), "CUT",   KEY_MACRO(0,KC_CUT), KEY_MACRO(0,0)),

  MACRO( CHORD(C,C,C,C), "F1",    KEY_MACRO(0,KC_FN(1)), KEY_MACRO(0,0)),
  MACRO( CHORD(C,C,M,M), "F2",    KEY_MACRO(0,KC_FN(2)), KEY_MACRO(0,0)),
  MACRO( CHORD(C,C,E,E), "F3",    KEY_MACRO(0,KC_FN(3)), KEY_MACRO(0,0)),

  MACRO( CHORD(C,C,O,C), "UDO",   KEY_MACRO(0,KC_UNDO), KEY_MACRO(0,0)),
  MACRO( CHORD(C,C,O,M), "RDO",   KEY_MACRO(0,KC_AGAIN), KEY_MACRO(0,0)),  //wtf is "REDO"?
//MACRO( CHORD(C,C,O,E), "",      str_macro("")),

  // page 6
  MACRO( CHORD(C,M,C,O), "&",     str_macro("&")),
  MACRO( CHORD(C,M,M,O), "0",     str_macro("0")),
  MACRO( CHORD(C,M,E,O), "\\",    str_macro("\\")),

  MACRO( CHORD(C,M,C,C), "F10",   KEY_MACRO(0,KC_FN(10)), KEY_MACRO(0,0)),
  MACRO( CHORD(C,M,M,M), "F11",   KEY_MACRO(0,KC_FN(11)), KEY_MACRO(0,0)),
  MACRO( CHORD(C,M,E,E), "F12",   KEY_MACRO(0,KC_FN(12)), KEY_MACRO(0,0)),

  MACRO( CHORD(C,M,C,C), "@",     str_macro("@")),
  MACRO( CHORD(C,M,M,M), "\"",    str_macro("\"")),
//MACRO( CHORD(C,M,E,E), "",      str_macro("")),

  // page 7
//MACRO( CHORD(C,E,C,O), "",      str_macro("")),
//MACRO( CHORD(C,E,M,O), "",      str_macro("")),
  MACRO( CHORD(C,E,E,O), "9",     str_macro("9")),

//MACRO( CHORD(C,E,C,C), "",      str_macro("")),
//MACRO( CHORD(C,E,M,M), "",      str_macro("")),
//MACRO( CHORD(C,E,E,E), "",      str_macro("")),

  MACRO( CHORD(C,E,C,C), "[",     str_macro("[")),
  MACRO( CHORD(C,E,M,M), "]",     str_macro("]")),
//MACRO( CHORD(C,E,E,E), "",      str_macro("")),


  // page 8
  MACRO( CHORD(O,M,C,O), "en",    str_macro("en")),
  MACRO( CHORD(O,M,M,O), "et",    str_macro("et")),
  MACRO( CHORD(O,M,E,O), "er",    str_macro("er")),

  MACRO( CHORD(O,M,C,C), "*",     str_macro("*")),
  MACRO( CHORD(O,M,M,M), "the",   str_macro("the")),
//MACRO( CHORD(O,M,E,E), "",      str_macro("")),

  MACRO( CHORD(O,M,C,C), "v",     str_macro("v")),
  MACRO( CHORD(O,M,M,M), "p",     str_macro("p")),
  MACRO( CHORD(O,M,E,E), "~",     str_macro("~")),

  // page 9
  MACRO( CHORD(M,C,C,O), ",",     str_macro(",")),
  MACRO( CHORD(M,C,M,O), "il",    str_macro("il")),
//MACRO( CHORD(M,C,E,O), "",      str_macro("")),

//MACRO( CHORD(M,C,C,C), "",      str_macro("")),
//MACRO( CHORD(M,C,M,M), "",      str_macro("")),
//MACRO( CHORD(M,C,E,E), "",      str_macro("")),

  MACRO( CHORD(M,C,C,C), "ac",    str_macro("ac")),
  MACRO( CHORD(M,C,M,M), "ch",    str_macro("ch")),
//MACRO( CHORD(M,C,E,E), "",      str_macro("")),

  // page 10
  MACRO( CHORD(M,M,C,O), "ed",    str_macro("ed")),
  MACRO( CHORD(M,M,M,O), "DEL",   KEY_MACRO(0,KC_DELETE), KEY_MACRO(0,0)),
  MACRO( CHORD(M,M,E,O), "q",     str_macro("q")),

  MACRO( CHORD(M,M,C,C), "F4",    KEY_MACRO(0,KC_FN(4)), KEY_MACRO(0,0)),
  MACRO( CHORD(M,M,M,M), "F5",    KEY_MACRO(0,KC_FN(5)), KEY_MACRO(0,0)),
  MACRO( CHORD(M,M,E,E), "F6",    KEY_MACRO(0,KC_FN(6)), KEY_MACRO(0,0)),

  MACRO( CHORD(M,M,C,C), "j",     str_macro("j")),
  MACRO( CHORD(M,M,M,M), "-",     str_macro("-")),
//MACRO( CHORD(M,M,E,E), "",      str_macro("")),

  // page 11
  MACRO( CHORD(M,E,C,O), "ion",   str_macro("ion")),
  MACRO( CHORD(M,E,M,O), ":",     str_macro(":")),
  MACRO( CHORD(M,E,E,O), "ou",    str_macro("ou")),

//MACRO( CHORD(M,E,C,C), "",      str_macro("")),
//MACRO( CHORD(M,E,M,M), "",      str_macro("")),
//MACRO( CHORD(M,E,E,E), "",      str_macro("")),

  MACRO( CHORD(M,E,O,C), "of",    str_macro("of")),
  MACRO( CHORD(M,E,O,M), "om",    str_macro("om")),
//MACRO( CHORD(M,E,O,E), "",      str_macro("")),

  // page 12
  MACRO( CHORD(O,E,C,O), "on",    str_macro("on")),
  MACRO( CHORD(O,E,M,O), "ot",    str_macro("ot")),
  MACRO( CHORD(O,E,E,O), "or",    str_macro("or")),

  MACRO( CHORD(O,E,C,C), "SEL",   KEY_MACRO(0,KC_SELECT), KEY_MACRO(0,0)), // wtf is "ALL"?
  MACRO( CHORD(O,E,M,M), "z",     str_macro("z")),
//MACRO( CHORD(O,E,E,E), "ENTER", KEY_MACRO(0,KC_ENTER), KEY_MACRO(0,0)), // wtf is "NL"?

  MACRO( CHORD(O,E,C,C), "/",     str_macro("/")),
  MACRO( CHORD(O,E,M,M), "b",     str_macro("b")),
  MACRO( CHORD(O,E,E,E), "%",     str_macro("%")),


  // page 13
  MACRO( CHORD(E,M,C,O), "HOM",   KEY_MACRO(0,KC_HOME), KEY_MACRO(0,0)),
  MACRO( CHORD(E,M,M,O), "PDN",   KEY_MACRO(0,KC_PAGE_UP), KEY_MACRO(0,0)),
  MACRO( CHORD(E,M,E,O), "END",   KEY_MACRO(0,KC_END), KEY_MACRO(0,0)),

//MACRO( CHORD(E,M,C,C), "",      str_macro("")),
//MACRO( CHORD(E,M,M,M), "",      str_macro("")),
//MACRO( CHORD(E,M,E,E), "",      str_macro("")),

  MACRO( CHORD(E,M,C,C), "INS",   KEY_MACRO(0,KC_INSERT), KEY_MACRO(0,0)),
  MACRO( CHORD(E,M,M,M), "PDN",   KEY_MACRO(0,KC_PAGE_DOWN), KEY_MACRO(0,0)),
//MACRO( CHORD(E,M,E,E), "CPS",   KEY_MACRO(0,KC_CAPS_LOCK), KEY_MACRO(0,0)), // wtf is "CPS"?

  // page 14
  MACRO( CHORD(E,E,C,O), "#",     str_macro("#")),
  MACRO( CHORD(E,E,M,O), "?",     str_macro("?")),
  MACRO( CHORD(E,E,E,O), ";",     str_macro(";")),

  MACRO( CHORD(E,E,C,C), "F7",    KEY_MACRO(0,KC_FN(7)), KEY_MACRO(0,0)),
  MACRO( CHORD(E,E,M,M), "F8",    KEY_MACRO(0,KC_FN(8)), KEY_MACRO(0,0)),
  MACRO( CHORD(E,E,E,E), "F9",    KEY_MACRO(0,KC_FN(9)), KEY_MACRO(0,0)),

  MACRO( CHORD(E,E,C,C), "<",     str_macro("<")),
  MACRO( CHORD(E,E,M,M), ">",     str_macro(">")),
//MACRO( CHORD(E,E,E,E), "",      str_macro("")),


  // page 15
  MACRO( CHORD(C,O,O,E), "ESC",   KEY_MACRO(0,KC_ESCAPE), KEY_MACRO(0,0)),
  MACRO( CHORD(M,O,O,E), "_",     str_macro("_")),
  MACRO( CHORD(E,O,O,E), "`",     str_macro("`")),

  MACRO( CHORD(O,C,O,E), "^",     str_macro("^")),
  MACRO( CHORD(O,M,O,E), "~",     str_macro("~")),
  MACRO( CHORD(O,E,O,E), "%",     str_macro("%")),

//MACRO( CHORD(O,O,C,E), "",      str_macro("")),
//MACRO( CHORD(O,O,M,E), "",      str_macro("")),
  MACRO( CHORD(O,O,E,E), "FND",   KEY_MACRO(0,KC_FIND), KEY_MACRO(0,0)),

  // page 16
  MACRO( CHORD(C,O,O,C), "5",     str_macro("5")),
  MACRO( CHORD(M,O,O,C), "f",     str_macro("f")),
  MACRO( CHORD(E,O,O,C), "as",    str_macro("as")),

  MACRO( CHORD(C,C,O,C), "UDO",   KEY_MACRO(0,KC_UNDO), KEY_MACRO(0,0)),
  MACRO( CHORD(M,M,O,C), "j",     str_macro("j")),
  MACRO( CHORD(E,E,O,C), "<",     str_macro("<")),

  MACRO( CHORD(O,C,O,C), "g",     str_macro("g")),
  MACRO( CHORD(O,M,O,C), "v",     str_macro("v")),
  MACRO( CHORD(O,E,O,C), "/",     str_macro("/")),

  MACRO( CHORD(O,C,C,C), "ing",   str_macro("ing")),
  MACRO( CHORD(O,M,M,C), "'",     str_macro("'")),
//MACRO( CHORD(O,E,E,C), "",      str_macro("")),

  MACRO( CHORD(O,O,C,C), "an",    str_macro("an")),
  MACRO( CHORD(O,O,M,C), "at",    str_macro("at")),
  MACRO( CHORD(O,O,E,C), "ar",    str_macro("ar")),


  // page 17
//MACRO( CHORD(C,O,M,C), "NAM",   str_macro("")), //wtf is NAM
  MACRO( CHORD(M,O,M,C), "al",    str_macro("al")),
//MACRO( CHORD(E,O,M,C), "",      str_macro("")),

  MACRO( CHORD(O,C,M,C), "|",     str_macro("|")),
  MACRO( CHORD(O,M,M,C), "'",     str_macro("'")),
  MACRO( CHORD(O,E,M,C), "$",     str_macro("$")),



  // page 18
//MACRO( CHORD(C,O,E,M), "",      str_macro("")),
  MACRO( CHORD(M,O,E,M), "=",     str_macro("=")),
//MACRO( CHORD(E,O,E,M), "",      str_macro("")),

//MACRO( CHORD(O,C,E,M), "",      str_macro("")),
//MACRO( CHORD(O,M,E,M), "",      str_macro("")),
  MACRO( CHORD(O,E,E,M), "!",     str_macro("!")),


  // page 19
  MACRO( CHORD(C,O,O,M), "_",     str_macro("_")),
  MACRO( CHORD(M,O,O,M), "_",     str_macro("_")),
  MACRO( CHORD(E,O,O,M), "`",     str_macro("`")),
  
  MACRO( CHORD(C,C,O,M), "RDO",   KEY_MACRO(0,KC_AGAIN), KEY_MACRO(0,0)),
  MACRO( CHORD(M,M,O,M), "-",     str_macro("-")),
  MACRO( CHORD(E,E,O,M), ">",     str_macro(">")),

  MACRO( CHORD(O,C,O,M), "y",     str_macro("y")),
  MACRO( CHORD(O,M,O,M), "p",     str_macro("p")),
  MACRO( CHORD(O,E,O,M), "b",     str_macro("b")),

//MACRO( CHORD(O,C,C,M), "",      str_macro("")),
  MACRO( CHORD(O,M,M,M), "the",   str_macro("the")),
  MACRO( CHORD(O,E,E,M), "!",     str_macro("!")),

//MACRO( CHORD(O,O,C,M), "",      str_macro("")),
  MACRO( CHORD(O,O,M,M), "th",    str_macro("th")),
  MACRO( CHORD(O,O,E,M), "x",     str_macro("x")),



  // not reachable, chord collision with Space earlier in table
  make_macro( CHORD(M,O,O,O),
    (macro_table_entry_t[]){
      str_macro("Gives Me the Screaming Heeby Jeebies")}),


  make_macro( CHORD(O,O,M,E), 
    konami_code),


};
extern const size_t macro_map_size = count(macro_map);

