#pragma once

#include <stdint.h>

class i2c_shim{
  public:

  i2c_shim(void* cxt): cxt(cxt){}
  void reg_write_uint8(uint8_t addr, uint8_t reg, uint8_t data);
  uint8_t reg_read_uint8(uint8_t addr, uint8_t reg);
  
  private:
  void* cxt;
};