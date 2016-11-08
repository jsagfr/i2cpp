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
  I2cDevice(const std::string& i2c, uint8_t addr);
  ~I2cDevice();

  template<class T> void write(T data);
  template<class T> void write(uint8_t reg, T data);
  template<class T> T read();
  template<class T> T read(uint8_t reg);


  // TODO: instantiate with std::enable_if<sizeof(T) == 1/2/4>
  // template<class T> T smbus_read(uint8_t reg);
#if defined (HAVE_SMBUS_READ_BYTE_DATA)
  uint8_t smbus_read_byte_data(uint8_t reg);
#endif

#if defined (HAVE_SMBUS_READ_WORD_DATA)
  uint16_t smbus_read_word_data(uint8_t reg);
#endif

#if defined (HAVE_SMBUS_READ_BLOCK_DATA)
  uint32_t smbus_read_block_data(uint8_t reg);
#endif

};

template<class T>
void I2cDevice::write(T data) {
  constexpr unsigned int s = sizeof(T);
  char buf[s] = {0};
  char * buf_data = reinterpret_cast<char *>(&data);
  for (unsigned int i = 0; i < s; i++)
    {
      buf[i] = buf_data[s-1-i];
    }
  
  if (::write(_file, buf, s) != s)
    {
      // TODO: Throw Error
      std::cerr << "Unable to read register on device." << std::endl;
      std::terminate();
    }
};

template<class T>
void I2cDevice::write(uint8_t reg, T data) {
  write(reg);
  write(data);
};


template<class T>
T I2cDevice::read() {
  constexpr unsigned int s = sizeof(T);
  char buf[s] = {0};
  if (::read(_file, buf, s) != s)
    {
      // TODO: Throw Error
      std::cerr << "Unable to read register on device." << std::endl;
      std::terminate();
    }
  return reinterpret_cast<T>(*buf);
};


template<class T>
T I2cDevice::read(uint8_t reg) {
  write(reg);
  return read<T>();
}

#endif  // I2C_DEVICE_H
