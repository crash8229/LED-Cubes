import pytest
import ledcube


def test_frame_v1():
    b = ledcube.serializer.frame_v1

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

    assert test_binary == data, "frame_v1 serializer did not build the same data as the frame_v1.bin binary"


def test_primary_header():
    b = ledcube.serializer.primary_header

    with open("../doc/file_specification/objects/frame/frame_v1.bin", "rb") as f:
        data = f.read()[:2]
    test_data = {
        "type": 0,
        "version": 1
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "primary header serializer did not build the same data as the primary header in frame_v1.bin binary"


def test_frame():
    b = ledcube.serializer.frame

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

    assert test_binary == data, "frame serializer did not build the same data as the frame_v1.bin binary"

def test_animation_v1():
    b = ledcube.serializer.animation_v1

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

    assert test_binary == data, "animation_v1 serializer did not build the same data as the animation_v1.bin binary"


def test_animation():
    b = ledcube.serializer.animation

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

    assert test_binary == data, "animation serializer did not build the same data as the animation_v1.bin binary"


def test_library_v1():
    b = ledcube.serializer.library_v1

    with open("../doc/file_specification/objects/library/library_v1.bin", "rb") as f:
        data = f.read()[2:]
    test_data = {
        "secondary_header": {
            "name": "Test Library",
            "time": 0x3E8,
            "crc": 0xFFFFFFFF,
            "tlc_count": 2,
            "animation_count": 2,
            "data_length": 0x1B2
        },
        "animations": [
            {
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
                                        "state": [0x111]*16
                                    },
                                    {
                                        "state": [0x222]*16
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
                                        "state": [0x333]*16
                                    },
                                    {
                                        "state": [0x444]*16
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
                                        "state": [0x555]*16
                                    },
                                    {
                                        "state": [0x666]*16
                                    }
                                ]
                            }
                        }
                    ]
                }
            },
            {
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
        ]
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "library_v1 serializer did not build the same data as the library_v1.bin binary"


def test_library():
    b = ledcube.serializer.library

    with open("../doc/file_specification/objects/library/library_v1.bin", "rb") as f:
        data = f.read()
    test_data = {
        "primary_header": {
            "type": 2,
            "version": 1
        },
        "library": {
            "secondary_header": {
                "name": "Test Library",
                "time": 0x3E8,
                "crc": 0xFFFFFFFF,
                "tlc_count": 2,
                "animation_count": 2,
                "data_length": 0x1B2
            },
            "animations": [
                {
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
                                            "state": [0x111]*16
                                        },
                                        {
                                            "state": [0x222]*16
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
                                            "state": [0x333]*16
                                        },
                                        {
                                            "state": [0x444]*16
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
                                            "state": [0x555]*16
                                        },
                                        {
                                            "state": [0x666]*16
                                        }
                                    ]
                                }
                            }
                        ]
                    }
                },
                {
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
            ]
        }
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "library serializer did not build the same data as the library_v1.bin binary"


def test_cube_file():
    b = ledcube.serializer.cube_file

    with open("../doc/file_specification/objects/cube_file/cube_file_v1.bin", "rb") as f:
        data = f.read()
    test_data = {
        "primary_header": {
            "type": 3,
            "version": 1
        },
        "file": {
            "primary_header": {
                "type": 2,
                "version": 1
            },
            "library": {
                "secondary_header": {
                    "name": "Test Library",
                    "time": 0x3E8,
                    "crc": 0xFFFFFFFF,
                    "tlc_count": 2,
                    "animation_count": 2,
                    "data_length": 0x1B2
                },
                "animations": [
                    {
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
                                                "state": [0x111]*16
                                            },
                                            {
                                                "state": [0x222]*16
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
                                                "state": [0x333]*16
                                            },
                                            {
                                                "state": [0x444]*16
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
                                                "state": [0x555]*16
                                            },
                                            {
                                                "state": [0x666]*16
                                            }
                                        ]
                                    }
                                }
                            ]
                        }
                    },
                    {
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
                ]
            }
        }
    }
    test_binary = b.build(test_data)

    assert test_binary == data, "cube_file serializer did not build the same data as the library_v1.bin binary"
