meta:
  id: file
  imports:
    - primary_header
    - library_v1
  endian: be

doc: LED Cube file

seq:
  - id: primary_header
    type: primary_header
  - id: file
    type:
      switch-on: primary_header.version
      cases:
        1: library_v1
    doc: The structure is determined by the version
  