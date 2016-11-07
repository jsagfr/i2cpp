cmake_minimum_required (VERSION 2.6)
project (i2c++)

include (CheckFunctionExists)
check_function_exists (i2c_smbus_read_byte_data HAVE_SMBUS_READ_BYTE_DATA)
check_function_exists (i2c_smbus_read_word_data HAVE_SMBUS_READ_WORD_DATA)
check_function_exists (i2c_smbus_read_block_data HAVE_SMBUS_READ_BLOCK_DATA)

configure_file (
  "${PROJECT_SOURCE_DIR}/I2cDeviceConfig.h.in"
  "${PROJECT_BINARY_DIR}/I2cDeviceConfig.h"
  )

include_directories(include)
include_directories("${PROJECT_BINARY_DIR}")

file(GLOB SOURCES "src/*.cpp")

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_executable(i2c++ ${SOURCES})

set_property(TARGET i2c++ PROPERTY CXX_STANDARD 11)
set_property(TARGET i2c++ PROPERTY CXX_STANDARD_REQUIRED ON)
