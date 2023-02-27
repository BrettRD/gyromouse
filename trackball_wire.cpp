
#include "Arduino.h"
#include "Wire.h"
#include "trackball_i2c_shim.hpp"

void i2c_shim::reg_write_uint8(uint8_t addr, uint8_t reg, uint8_t data){
  TwoWire* wire = (TwoWire*) cxt;

  wire->beginTransmission(addr);
  wire->write(reg);
  wire->write(data);
  wire->endTransmission();
}

uint8_t i2c_shim::reg_read_uint8(uint8_t addr, uint8_t reg){
  TwoWire* wire = (TwoWire*) cxt;
  uint8_t value;
  wire->beginTransmission(addr);
  wire->write(reg);
  Wire.endTransmission(false); // false to not release the line

  wire->requestFrom(addr, (uint8_t) 1);
  wire->readBytes(&value, (uint8_t) 1);
  return value;
}