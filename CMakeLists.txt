cmake_minimum_required (VERSION 2.6)
project (i2c++)

include (CheckIncludeFiles)
include (CheckSymbolExists)

check_include_files ("linux/i2c-dev.h" HAVE_I2C_DEV_H)
if(NOT HAVE_I2C_DEV_H)
  message( FATAL_ERROR "No linux/i2c-dev.h found" )
endif()

check_symbol_exists (i2c_smbus_read_byte_data linux/i2c-dev.h HAVE_SMBUS_READ_BYTE_DATA)
check_symbol_exists (i2c_smbus_read_word_data linux/i2c-dev.h HAVE_SMBUS_READ_WORD_DATA)
check_symbol_exists (i2c_smbus_read_block_data linux/i2c-dev.h HAVE_SMBUS_READ_BLOCK_DATA)

configure_file (
  "${PROJECT_SOURCE_DIR}/I2cDeviceConfig.h.in"
  "${PROJECT_BINARY_DIR}/I2cDeviceConfig.h"
  )

add_library(i2c++ src/I2cDevice.cpp)

add_compile_options(-Wall)
add_compile_options(-Wextra)
set_property(TARGET i2c++ PROPERTY CXX_STANDARD 11)
set_property(TARGET i2c++ PROPERTY CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

target_include_directories(i2c++ PUBLIC include)

install(TARGETS i2c++ DESTINATION lib)
install(FILES include/I2cDevice.h DESTINATION include/i2c++)
