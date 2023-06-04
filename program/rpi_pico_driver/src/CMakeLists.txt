# Add executable
set(executable_name ${CMAKE_PROJECT_NAME})
add_executable(${executable_name} main.cpp)
pico_set_program_name(${executable_name} "5x5 LED Cube RPi Pico Driver")
pico_set_program_version(${executable_name} "0.1")

# Add include directory
target_include_directories(${executable_name}
        PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/include/parser"
        )

# Add source files
target_sources(${executable_name} PRIVATE
        tlc5940.cpp
        ledcube.cpp
        sdcard.cpp
        )

# Configure PICO stdio
pico_enable_stdio_uart(${executable_name} 1)
pico_enable_stdio_usb(${executable_name} 1)

# Add library for SD card
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/spi_sd_fat/src" build/sdcard)

# Add parsers
add_subdirectory("parser")

# Link the standard library to the build
target_link_libraries(${executable_name}
        pico_stdlib
        )

# Link any user requested libraries
target_link_libraries(${executable_name}
        pico_multicore
        hardware_spi
        hardware_i2c
        FatFs_SPI
        )

#create files beyond the executable (.uf2, .hex, .bin, .map, .dis) using an SDK provided function
pico_add_extra_outputs(${executable_name})
