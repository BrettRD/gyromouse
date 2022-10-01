
#include "chordtools.h"
#include "key_ascii_map.h"

void compare_chords(void* cxt, chord_t old_chord, chord_t new_chord){
  chord_t release = old_chord & (~new_chord);
  chord_t press = new_chord & (~old_chord);

  if((press == 0) && (release != 0)){
    //release_cb(old_chord);
  }
}

chord_t released_chord(chord_t old_chord, chord_t new_chord){
  if ( old_chord & (~new_chord) ){
    return old_chord;
  }
  return 0;
}


void send_macro(BleGyroMouse* keyb, const chordmacro_t* macro){
  const macro_table_entry_t* report = macro->macro;
  uint8_t buf[keyboard_report_len] {0};

  for(size_t i=0; i<macro->n_reports; i++){

    switch(report[i].type){
      case KEYREPORT:
        keyb->send_keyboard_report(
          pack_keyboard_report(
            report[i].key->modifiers,
            report[i].key->keys,
            buf
          )
        );
        break;

      case MEDIAREPORT:
        break;
      case STRING:
        send_string_as_keyreps(keyb, report[i].string);

        break;
      default:
        break;

    }
  }
}

void send_string_as_keyreps(BleGyroMouse* keyb, const char* str){
  uint8_t buf[keyboard_report_len] {0};
  size_t key_idx = 0;
  keyreport_t keyrep = {0};
  char c;
  uint8_t scan_code;
  uint8_t mod;
  bool duplicate;

  // fetch a character and advance the string
  c = *(str++);
  // check if we need to use the shift key
  mod = KC_SHIFT(c) ? KM_L_SHIFT : 0;
  // pick the scan code
  scan_code = KC_CHAR(c);

  while (scan_code != '\0'){
    keyrep.modifiers = mod;
    keyrep.keys[key_idx++] = scan_code;

    // fetch a character and advance the string
    c = *(str++);
    // check if we need to use the shift key
    mod = KC_SHIFT(c) ? KM_L_SHIFT : 0;
    // pick the scan code
    scan_code = KC_CHAR(c);

    // check for dupliate keystrokes, they need to be sent as new reports
    duplicate=false;
    for(size_t past_idx = 0; past_idx < key_idx; past_idx++){
      if(scan_code == keyrep.keys[past_idx])
      {
        duplicate = true;
      }
    }
    // check if we need to split the string into a new report
    if( (keyrep.modifiers != mod) ||  // shift needs to be pressed or released, 
        (key_idx == 6) ||             // the key report is full
        (scan_code == '\0') ||        // we've reached the end of the string
        (duplicate == true)           // we need to send a repeated keystroke
      )
    {

      keyb->send_keyboard_report(
        pack_keyboard_report(
          keyrep.modifiers,
          keyrep.keys,
          buf
        )
      );

      // if a key is pressed in two subsequent reports,
      // it is considered held for both reports.
      // release all keys to allow repeated keypresses
      key_idx = 0;
      memset(keyrep.keys, 0, 6);

      keyb->send_keyboard_report(
        pack_keyboard_report(
          0,//keyrep.modifiers, // send a fully open key map so we can safely stop here
          keyrep.keys,
          buf
        )
      );

    }

  }
}


const chordmacro_t* search_chord_table(
  chord_t chord,
  const chordmacro_t* table,
  size_t table_size
){
  for(size_t i=0; i<table_size; i++)
  {
    if(chord == table[i].chord){
      return &table[i];
    }
  }
  return NULL;
}



const int table_cols = 4;
const int table_rows = 5;
const chord_t macro_print_masks[table_cols * table_rows] = {
  CHORD(O,O,O,O), CHORD(C,O,O,O), CHORD(M,O,O,O), CHORD(E,O,O,O),
  CHORD(O,C,O,O), CHORD(C,C,O,O), CHORD(C,M,O,O), CHORD(C,E,O,O),
  CHORD(O,M,O,O), CHORD(M,C,O,O), CHORD(M,M,O,O), CHORD(M,E,O,O),
  CHORD(O,E,O,O), CHORD(E,M,O,O), CHORD(E,E,O,O), CHORD(O,O,O,E),
  CHORD(O,O,O,C), CHORD(O,O,M,C), CHORD(O,O,E,M), CHORD(O,O,O,M)
};


void print_macro_table(
  const chordmacro_t* table,
  size_t table_len,
  void (*callback)(const char*)
  ){
    callback("\nCheat Sheet:\n");

    const size_t chord_width  = 5; // the number of characters to render each chord
    const size_t chord_cols = 3; // the number of columns of chords per table cell
    const size_t chord_rows = 7; // the number of rows of chords per table cell
    const size_t cell_width = chord_width * chord_cols; // the width (in chars) of each table cell

    const size_t table_width = cell_width * table_cols + (table_cols+1); //four cols, five separators
    const size_t table_height = chord_rows * table_rows + (table_rows+1); // five rows each with seven lines, six separators

    const size_t buflen = table_width+3; //newline, null

    char buf[buflen] = ""; //render the table line by line
    char* cursor; // to incrementally walk the buffer

    const char* label = "";     // marker for the chord
    size_t label_len = 0; // length of the marker
    int space_pre = 0;    // blank space before the marker 
    int space_post = 0;   // blank space after the marker 
    int table_row = 0;    // vertical index of the chord block
    int table_col=0;      // horizontal index of the chord block
    int cell_line = 0;    // line number within the chord block
    int cell_col = 0;     // horizontal index of a chord label within a chord block

    chord_t chord_fixed = 0;      // fixed fingering in this table cell
    chord_t chord_line_mask = 0;  // buttons active on this row within a table cell
    chord_t chord_col_mask = 0;   // buttons active on this column within a table cell
    chord_t chord = 0;            // the chord being rendered

    char tmp_label[10] = "\0\0\0\0\0\0\0\0\0";

    for(int line = 0; line < table_height; line++){
      table_row = (line / (chord_rows+1)) % table_rows;  // wrap to avoid array overrun
      cell_line = line % (chord_rows+1);

      for(table_col=0; table_col<table_cols; table_col++){
        // seek to the beginning of the cell
        cursor = &buf[table_col*(cell_width+1)];
        // print a vertical separator
        *(cursor++) = '|';
        //*(cursor++) = '0'+cell_line;

        //  find the fixed fingering for this table cell
        chord_fixed = macro_print_masks[table_col + table_row*table_cols];
        
        // figure out which keys we collide with
        chord_line_mask = ((const chord_t[]){
          CHORD(O,O,O,O), // empty for h line
          CHORD(A,O,O,O),
          CHORD(A,A,O,O),
          CHORD(O,A,O,O),
          CHORD(O,A,A,O),
          CHORD(O,O,A,O),
          CHORD(O,O,A,A),
          CHORD(O,O,O,A),
        })[cell_line];

        for(cell_col=0; cell_col<3; cell_col++){
          // pick a finger pos
          FingerPos f = ((const FingerPos[]){C,M,E})[cell_col];
          chord_col_mask = CHORD(f,f,f,f);

          if(cell_line == 0){
            // print some horizontal line
            label = "------------------------------"; // XXX dynamically set this
          }
          else if(chord_fixed & chord_line_mask)
          {
            // The fixed fingering collides with the row we're rendering
            // combine the cell pos fingering with the cell fixed fingering
            
            // just place a dot indicating the fixed fingering for the cell
            chord = (chord_line_mask & chord_col_mask & chord_fixed);
            
            label = "";
            // ignore even lines where the mask has two buttons
            if((cell_line & 1) && (chord))
              label = "{*}";

          }
          else
          { 
            // render this line with chord labels
            // combine the cell pos fingering with the cell fixed fingering
            chord = (chord_line_mask & chord_col_mask) | chord_fixed;
            //tmp_label[0] = (chord == CHORD(M,M,O,O)) ? 'T' : 'F';
            //label = tmp_label;
            // look up the macro and fetch the label
            label = "";
            const chordmacro_t* macro = search_chord_table(chord, table, table_len);
            if(macro) label = macro->name;

          }

          // check the label fits
          label_len = strlen(label);
          if(label_len > chord_width) label_len = chord_width;
          // compute the number of spaces before and after the label

          space_pre = chord_width/2 - label_len/2;
          //if(0 == (cell_line & 1)) space_pre += 1;  // indent even lines
          space_post = chord_width - label_len - space_pre;
          // put the label in the buffer
          memset(cursor, ' ', space_pre);
          cursor += space_pre;
          memcpy(cursor, label, label_len);
          cursor += label_len;
          memset(cursor, ' ', space_post);
          cursor += space_post;

        }

      }
      // end the line
      buf[table_width-1] = '|';
      buf[table_width] = '\n';
      buf[table_width+1] = '\0';
      callback(buf);
    }



  }
