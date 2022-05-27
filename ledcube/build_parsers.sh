#!/bin/bash

pushd ./ledcube/parser/
kaitai-struct-compiler -t python --python-package ledcube.parser ../../../doc/file_specification/parser.ksy ../../../doc/file_specification/objects/cube_file.ksy
popd

# Patch parser.py
./parser_patch.sh
