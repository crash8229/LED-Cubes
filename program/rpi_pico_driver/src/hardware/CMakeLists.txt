# Add include directory
target_include_directories(${executable_name}
        PUBLIC
        "${PROJECT_SOURCE_DIR}/include/hardware"
        )

# Add source files
target_sources(${executable_name} PRIVATE
        tlc5940.cpp
        sdcard.cpp
        )
