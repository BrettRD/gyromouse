#include "pcf8574_wire.h"
#include "pcf8574.h"

void PCF8574_read_io(void* cxt, uint8_t* data){
  wire_cxt* w = (wire_cxt*)cxt;
  if (w->wire->requestFrom(w->addr, (uint8_t)1) == 1)
    *data = w->wire->read();
}
void PCF8574_write_io(void* cxt, uint8_t data){
  wire_cxt* w= (wire_cxt*)cxt;
  w->wire->beginTransmission(w->addr);
  w->wire->write(data);
  w->wire->endTransmission();
}
