# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

# initialize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(rpi_pico_driver C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 0)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(rpi_pico_driver main.cpp tlc5940.cpp tlc5940.h w25q64.cpp w25q64.h)

pico_set_program_name(rpi_pico_driver "RPi Pico Driver")
pico_set_program_version(rpi_pico_driver "0.1")

pico_enable_stdio_uart(rpi_pico_driver 1)
pico_enable_stdio_usb(rpi_pico_driver 0)

# Add the standard library to the build
target_link_libraries(rpi_pico_driver pico_stdlib)

# Add any user requested libraries
target_link_libraries(rpi_pico_driver
        hardware_spi
        hardware_i2c
        )

#create files beyond the executable (.uf2, .hex, .bin, .map, .dis) using an SDK provided function
pico_add_extra_outputs(rpi_pico_driver)
