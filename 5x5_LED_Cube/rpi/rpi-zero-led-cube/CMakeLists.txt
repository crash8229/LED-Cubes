cmake_minimum_required(VERSION 3.0)
project(rpi_led_cube)

set(CMAKE_CXX_STANDARD 14)

include(Findpigpio.cmake)
include_directories(${pigpio_INCLUDE_DIR})

add_executable(rpi_led_cube main.cpp TLC5940.cpp TLC5940.h LedCube5x5.cpp LedCube5x5.h)
target_link_libraries(rpi_led_cube ${pigpio_LIBRARY} ${pigpiod_if_LIBRARY} ${pigpiod_if2_LIBRARY})
