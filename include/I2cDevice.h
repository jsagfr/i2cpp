#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include "I2cDeviceConfig.h"

// For C open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// For C close
#include <unistd.h>


class I2cDevice
{
protected:
  int _file;
  const char* _i2c;
  uint8_t _addr;

public:
  I2cDevice(const char* i2c, uint8_t addr);
  I2cDevice(const std::string& i2c, uint8_t addr);
  ~I2cDevice();

  void write(const uint8_t* data, size_t s);
  void write(uint8_t* data, size_t s);
  void write(std::initializer_list<uint8_t> data);

  template <typename T>
  T read() {
    std::array<char, sizeof(T)> buf;
    if (::read(_file, buf.data(), sizeof(T)) != sizeof(T)) {
      // TODO: Error
    }
    return  *reinterpret_cast<T*>(buf.data());
  }
  
#if defined (HAVE_SMBUS_READ_BYTE_DATA)
  uint8_t smbus_read_byte_data(uint8_t reg);
#endif

#if defined (HAVE_SMBUS_READ_WORD_DATA)
  uint16_t smbus_read_word_data(uint8_t reg);
#endif

#if defined (HAVE_SMBUS_READ_BLOCK_DATA)
  uint32_t smbus_read_block_data(uint8_t reg);
#endif

#if defined (HAVE_I2C_SMBUS_WRITE_BYTE_DATA)
  void smbus_write(uint8_t reg, uint8_t data);
#endif
#if defined (HAVE_I2C_SMBUS_WRITE_WORD_DATA)
  void smbus_write(uint8_t reg, uint16_t data);
#endif
  
};


#endif  // I2C_DEVICE_H
