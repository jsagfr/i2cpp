cmake_minimum_required (VERSION 2.6)
project (i2c++)

# include (CheckIncludeFile)
# include (CheckIncludeFileCXX)
include (CheckIncludeFiles)
# include (CheckFunctionExists)
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

include_directories("${PROJECT_BINARY_DIR}")
include_directories(include)


file(GLOB SOURCES "src/*.cpp")

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_executable(i2c++ ${SOURCES})

set_property(TARGET i2c++ PROPERTY CXX_STANDARD 11)
set_property(TARGET i2c++ PROPERTY CXX_STANDARD_REQUIRED ON)
