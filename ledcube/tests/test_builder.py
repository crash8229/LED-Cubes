import pytest
import ledcube


def test_frame_v1():
    b = ledcube.builder.frame_v1

    with open("../doc/file_specification/objects/frame/frame_v1.bin", "rb") as f:
        data = f.read()[2:]
    test_data = {
        "secondary_header": {"duration": 5, "data_length": 48},
        "tlc_states": [{"state": [0xAAA]*16}, {"state": [0xBBB]*16}]
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "frame_v1 builder did not build the same data as the frame_v1.bin binary"
