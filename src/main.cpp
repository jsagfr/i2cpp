#include <iostream>
#include <cstdint>
#include <bitset>
#include "I2cDevice.h"

const uint8_t accAddr {0x6b};
const uint8_t whoAmI {0x0f};

int main()
{
  I2cDevice acc("/dev/i2c-2", accAddr);

  std::cout << "I am : " << std::bitset<8>(acc.read<char>(whoAmI)) << std::endl;

#if defined (HAVE_SMBUS_READ_BYTE_DATA)
  uint8_t iAm = acc.smbus_read_byte_data(whoAmI);
  std::cout << "I am : " << std::bitset<8>(iAm) << " (smbus version)" << std::endl;
#endif

  exit(EXIT_SUCCESS);
}
