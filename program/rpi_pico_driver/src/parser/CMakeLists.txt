# Add include directory
target_include_directories(${executable_name}
        PUBLIC
        "${PROJECT_SOURCE_DIR}/include/parser"
        )

# Add source files
target_sources(${executable_name} PRIVATE
        parserbase.cpp
        primaryheader.cpp
        frame.cpp
        )
