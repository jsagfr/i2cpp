cmake_minimum_required (VERSION 2.6)
project (i2c++)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_executable(i2c++ ${SOURCES})

set_property(TARGET i2c++ PROPERTY CXX_STANDARD 11)
set_property(TARGET i2c++ PROPERTY CXX_STANDARD_REQUIRED ON)
