#ifndef KEYSCAN_H
#define KEYSCAN_H

#include <stdint.h>
#include "pcf8574.h"


typedef uint32_t chord_t;
bool keyb_int_valid(chord_t chord);

void keyscan(void* cxt, chord_t* chord);

#endif //KEYSCAN_H