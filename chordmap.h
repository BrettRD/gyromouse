#ifndef CHORDMAP_H
#define CHORDMAP_H
#include "chordtools.h"

const uint8_t mouse_mask = ((CHORD_MOUSE_L)|(CHORD_MOUSE_M)|(CHORD_MOUSE_R));
uint8_t mouse_buttons(chord_t chord);
extern const chordmacro_t macro_map[];
extern const size_t macro_map_size;

#endif //CHORDMAP_H