#include "I2cDevice.h"
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <iostream>

I2cDevice::I2cDevice(const char* i2c, uint8_t addr) :
  _file(-1),
  _addr(addr)
{
  // const char *filename = i2c.c_str();
  if ((_file = open(i2c, O_RDWR)) < 0)
    {
      // TODO: Throw an error
      std::cerr << "Failed to open the bus." << std::endl;
      exit(1);
    }
  if (ioctl(_file, I2C_SLAVE, _addr) < 0)
    {
      // TODO: Throw an error
      std::cerr << "Failed to acquire bus access and/or talk to slave." << std::endl;
      exit(1);
    }
}

// I2cDevice::I2cDevice(std::string& const i2c, uint8_t addr) :
//   I2cDevice(i2c.c_str(), addr)
// {
// }

I2cDevice::~I2cDevice()
{
  close(_file);
}

#if defined (HAVE_SMBUS_READ_BYTE_DATA)
uint8_t I2cDevice::smbus_read_byte_data(uint8_t reg)
{
  return i2c_smbus_read_byte_data(_file, reg);
}
#endif

#if defined (HAVE_SMBUS_READ_WORD_DATA)
uint16_t I2cDevice::smbus_read_word_data(uint8_t reg)
{
  return i2c_smbus_read_byte_data(_file, reg);
}
#endif

#if defined (HAVE_SMBUS_READ_BLOCK_DATA)
uint32_t I2cDevice::smbus_read_block_data(uint8_t reg)
{
  return i2c_smbus_read_byte_data(_file, reg);
}
#endif
