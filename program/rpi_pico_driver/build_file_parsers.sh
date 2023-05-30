#!/bin/bash

# Generate parsers for C++
mkdir -p ./src/parsers
kaitai-struct-compiler --target cpp_stl --cpp-standard 98 --outdir ./src/parsers ./extern/led-cube-data/doc/file_specification/parser.ksy

# Generate CMakeLists.txt
echo -e "# Add source files\ntarget_sources(\${executable_name} PRIVATE" > ./src/parsers/CMakeLists.txt
for entry in ./src/parsers/*.cpp; do
  echo "        $(basename "$entry")" >> ./src/parsers/CMakeLists.txt
done
echo -e "        )" >> ./src/parsers/CMakeLists.txt
