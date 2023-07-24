
#include "Arduino.h"
#include "Wire.h"


typedef struct {
  TwoWire* wire;
  uint8_t addr;
} wire_cxt; 
