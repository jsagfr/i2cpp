#include <iostream>
#include <cstdint>
#include <bitset>
#include "I2cDevice.h"

const uint8_t accAddr {0x6b};
const uint8_t whoAmI {0x0f};

int main()
{
  I2cDevice acc("/dev/i2c-2", accAddr);
  
  std::cout << "I am : " << std::bitset<8>(acc.read(whoAmI)) << std::endl;
  // acc.write(reg, value);

  exit(EXIT_SUCCESS);
}
