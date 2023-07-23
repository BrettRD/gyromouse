/*
This is the API for interacting with the PCF8574
IO is open-collector with a weak pull-up.
This chip has no registers, access is to a single byte.

When you implement these calls with a specific I2C lib,
    pass everything the I2C bus needs as a pointer to a struct
    in the context pointer
*/



// read a single byte from the device
void PCF8574_read_io(void* cxt, uint8_t* data);

// write a single byte to the device
void PCF8574_write_io(void* cxt, uint8_t data);
