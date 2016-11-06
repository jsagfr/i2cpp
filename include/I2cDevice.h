#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <string>

class I2cDevice
{
protected:
  int _file;
  uint8_t _addr;

public:
  I2cDevice(const char* i2c, uint8_t addr);
  // I2cDevice(std::string& const i2c, uint8_t addr);
  ~I2cDevice();

  uint8_t read(uint8_t reg);
  /* uint16_t read(uint8_t reg); */
};

#endif  // I2C_DEVICE_H
