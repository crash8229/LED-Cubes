import pytest
import ledcube


def test_frame_v1():
    b = ledcube.builder.frame_v1

    with open("../doc/file_specification/objects/frame/frame_v1.bin", "rb") as f:
        data = f.read()[2:]
    test_data = {
        "secondary_header": {
            "duration": 5,
            "data_length": 48
        },
        "tlc_states": [
            {
                "state": [0xAAA]*16
            },
            {
                "state": [0xBBB]*16
            }
        ]
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "frame_v1 builder did not build the same data as the frame_v1.bin binary"


def test_primary_header():
    b = ledcube.builder.primary_header

    with open("../doc/file_specification/objects/frame/frame_v1.bin", "rb") as f:
        data = f.read()[:2]
    test_data = {
        "type": 0,
        "version": 1
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "primary header builder did not build the same data as the primary header in frame_v1.bin binary"


def test_frame():
    b = ledcube.builder.frame

    with open("../doc/file_specification/objects/frame/frame_v1.bin", "rb") as f:
        data = f.read()
    test_data = {
        "primary_header": {
            "type": 0,
            "version": 1
        },
        "frame": {
            "secondary_header": {
                "duration": 5,
                "data_length": 48
            },
            "tlc_states": [
                {
                    "state": [0xAAA]*16
                },
                {
                    "state": [0xBBB]*16
                }
            ]
        }
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "frame builder did not build the same data as the frame_v1.bin binary"

def test_animation_v1():
    b = ledcube.builder.animation_v1

    with open("../doc/file_specification/objects/animation/animation_v1.bin", "rb") as f:
        data = f.read()[2:]
    test_data = {
        "secondary_header": {
            "name": "Test",
            "time": 0x3E8,
            "crc": 0xFFFFFFFF,
            "tlc_count": 2,
            "frame_count": 3,
            "data_length": 0xA2
        },
        "frames": [
            {
                "primary_header": {
                    "type": 0,
                    "version": 1
                },
                "frame": {
                    "secondary_header": {
                        "duration": 5,
                        "data_length": 48
                    },
                    "tlc_states": [
                        {
                            "state": [0xAAA]*16
                        },
                        {
                            "state": [0xBBB]*16
                        }
                    ]
                }
            },
            {
                "primary_header": {
                    "type": 0,
                    "version": 1
                },
                "frame": {
                    "secondary_header": {
                        "duration": 5,
                        "data_length": 48
                    },
                    "tlc_states": [
                        {
                            "state": [0xCCC]*16
                        },
                        {
                            "state": [0xDDD]*16
                        }
                    ]
                }
            },
            {
                "primary_header": {
                    "type": 0,
                    "version": 1
                },
                "frame": {
                    "secondary_header": {
                        "duration": 5,
                        "data_length": 48
                    },
                    "tlc_states": [
                        {
                            "state": [0xEEE]*16
                        },
                        {
                            "state": [0xFFF]*16
                        }
                    ]
                }
            }
        ]
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "animation_v1 builder did not build the same data as the animation_v1.bin binary"


def test_animation():
    b = ledcube.builder.animation

    with open("../doc/file_specification/objects/animation/animation_v1.bin", "rb") as f:
        data = f.read()
    test_data = {
        "primary_header": {
            "type": 1,
            "version": 1
        },
        "animation": {
            "secondary_header": {
                "name": "Test",
                "time": 0x3E8,
                "crc": 0xFFFFFFFF,
                "tlc_count": 2,
                "frame_count": 3,
                "data_length": 0xA2
            },
            "frames": [
                {
                    "primary_header": {
                        "type": 0,
                        "version": 1
                    },
                    "frame": {
                        "secondary_header": {
                            "duration": 5,
                            "data_length": 48
                        },
                        "tlc_states": [
                            {
                                "state": [0xAAA]*16
                            },
                            {
                                "state": [0xBBB]*16
                            }
                        ]
                    }
                },
                {
                    "primary_header": {
                        "type": 0,
                        "version": 1
                    },
                    "frame": {
                        "secondary_header": {
                            "duration": 5,
                            "data_length": 48
                        },
                        "tlc_states": [
                            {
                                "state": [0xCCC]*16
                            },
                            {
                                "state": [0xDDD]*16
                            }
                        ]
                    }
                },
                {
                    "primary_header": {
                        "type": 0,
                        "version": 1
                    },
                    "frame": {
                        "secondary_header": {
                            "duration": 5,
                            "data_length": 48
                        },
                        "tlc_states": [
                            {
                                "state": [0xEEE]*16
                            },
                            {
                                "state": [0xFFF]*16
                            }
                        ]
                    }
                }
            ]
        }
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "animation builder did not build the same data as the animation_v1.bin binary"
