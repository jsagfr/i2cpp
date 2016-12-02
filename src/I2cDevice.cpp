#include "I2cDevice.h"

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

#include <cstring>
#include <cerrno>

#include <cstdio>
// For C open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// For C close
#include <unistd.h>
// For i2c
#include <linux/i2c-dev.h>
// For ioctl
#include <sys/ioctl.h>


I2cDevice::I2cDevice(const char* i2c, uint8_t addr) :
  _file(-1),
  _i2c(i2c),
  _addr(addr)
{
  // const char *filename = i2c.c_str();
  if ((_file = ::open(i2c, O_RDWR | O_SYNC )) < 0)
    {
      std::ostringstream e;
      e << "unable to open '" << _i2c << "': " << std::strerror(errno);
      throw std::ios_base::failure(e.str());
    }
  if (ioctl(_file, I2C_SLAVE, _addr) < 0)
    {
      std::ostringstream e;
      e << "in '" << _i2c << "'" << ", unable to set '" << _addr << "' as i2c slave: "
	<< std::strerror(errno);
      throw std::ios_base::failure(e.str());
    }
}

I2cDevice::I2cDevice(const std::string& i2c, uint8_t addr) :
  I2cDevice(i2c.c_str(), addr)
{
}

I2cDevice::~I2cDevice()
{
  ::close(_file);
}

inline void I2cDevice::write(uint8_t* data, size_t s) {
  write(data, s);
}

void I2cDevice::write(const uint8_t* data, size_t s)
{
  if (::write(_file, data, s) != s)
    {
      std::ostringstream e;
      e << "in '" << _i2c << "'" << " for device '" << _addr << "', unable to write data: "
	<< std::strerror(errno);
      throw std::ios_base::failure(e.str());
    }
  std::cout << "I2cDevice::write(const vector<uint8_t> data): '";
  std::vector<uint8_t> v(data, data + s);
  for(auto c: v)
    std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(c) << " ";
  std::cout << "'" << std::endl;
}

void I2cDevice::write(std::initializer_list<uint8_t> data) {
  write(data.begin(), data.size());
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

#if defined (HAVE_I2C_SMBUS_WRITE_BYTE_DATA)
void I2cDevice::smbus_write(uint8_t reg, uint8_t data)
{
  if (i2c_smbus_write_byte_data(_file, reg, data) < 0)
    {
      std::cerr << "Error in i2c_smbus_write_byte_data" << std::endl;
      // TODO throw
    }
  std::cout << "I2cDevice::smbus_write(uint8_t reg, uint8_t data): reg: '" << std::hex << static_cast<int>(reg) << "' data: '" << std::hex << static_cast<int>(data) << "'" << std::endl;
}
#endif
#if defined (HAVE_I2C_SMBUS_WRITE_WORD_DATA)
void I2cDevice::smbus_write(uint8_t reg, uint16_t data)
{
  if (i2c_smbus_write_word_data(_file, reg, data) < 0)
    {
      std::cerr << "Error in i2c_smbus_write_word_data" << std::endl;
      // TODO throw
    }
  std::cout << "I2cDevice::smbus_write(uint8_t reg, uint16_t data): reg: '" << std::hex << static_cast<int>(reg) << "' data: '" << std::hex << static_cast<int>(data) << "'" << std::endl;
}
#endif
