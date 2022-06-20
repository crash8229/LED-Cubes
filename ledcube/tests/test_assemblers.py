from ledcube import assemblers
from ledcube.parser import frame


def test_frame_v1():
    with open("../doc/file_specification/objects/frame/frame_v1.bin", "rb") as f:
        data = f.read()

    obj = assemblers.FrameV1(duration=5, tlc_states=[[0xAAA]*16, [0xBBB]*16])

    assert obj.generate() == data, "frame_v1 assembler did not build the same data as the frame_v1.bin binary"

def test_animation_v1():
    with open("../doc/file_specification/objects/animation/animation_v1.bin", "rb") as f:
        data = f.read()

    obj = assemblers.AnimationV1(
        name="Test",
        timestamp=0x3E8,
        tlc_count=2,
        frame_count=3,
        frames=[
            assemblers.FrameV1(duration=5, tlc_states=[[0xAAA]*16,[0xBBB]*16]),
            assemblers.FrameV1(duration=5, tlc_states=[[0xCCC]*16,[0xDDD]*16]),
            assemblers.FrameV1(duration=5, tlc_states=[[0xEEE]*16,[0xFFF]*16]),
        ]
        )

    assert obj.generate() == data, "animation_v1 assembler did not build the same data as the animation_v1.bin binary"
