#!/bin/bash

pushd ./ledcube/parser/
kaitai-struct-compiler -t python --python-package ledcube.parser ../../../doc/file_specification/parser.ksy
popd

# Patch parser.py
./parser_patch.sh
