# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

# Global Variables -----------------------------------------------------------------------------------------------------

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

set(PICO_CXX_ENABLE_EXCEPTIONS 0)

# Add cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# initialize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}")

# Modules --------------------------------------------------------------------------------------------------------------

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import)

# Libraries ------------------------------------------------------------------------------------------------------------

# Additional Pre-project Setup -----------------------------------------------------------------------------------------

# Project --------------------------------------------------------------------------------------------------------------
project(rpi_pico_driver C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Subdirectories
add_subdirectory(src)
