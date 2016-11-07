#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <string>
#include <iostream>
#include <exception>

#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include "I2cDeviceConfig.h"

class I2cDevice
{
protected:
  int _file;
  uint8_t _addr;

public:
  I2cDevice(const char* i2c, uint8_t addr);
  // I2cDevice(std::string& const i2c, uint8_t addr);
  ~I2cDevice();

  template<class T> T read(uint8_t reg);


  // TODO: instantiate with std::enable_if<sizeof(T) == 1/2/4>
  // template<class T> T smbus_read(uint8_t reg);
#if defined (HAVE_SMBUS_READ_BYTE_DATA)
  int8_t smbus_read_data(reg uint8_t);
#endif

#if defined (HAVE_SMBUS_READ_WORD_DATA)
  int16_t smbus_read_data(reg uint8_t);
#endif

#if defined (HAVE_SMBUS_READ_BLOCK_DATA)
  int32_t smbus_read_data(reg uint8_t);
#endif

};


template<class T>
T I2cDevice::read(uint8_t reg) {
  constexpr unsigned int s = sizeof(T);
  char buf[s] = {0};
  buf[0] = reg;
  if (read(_file, buf, s) != s)
    {
      // TODO: Throw Error
      std::cerr << "Unable to read register on device." << std::endl;
      std::terminate();
    }
  return reinterpret_cast<T>(*buf);
}

#endif  // I2C_DEVICE_H
