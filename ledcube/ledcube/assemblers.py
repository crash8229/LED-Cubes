from binascii import crc32
from copy import deepcopy
from typing import Sequence, Dict, Any
from construct import SizeofError

from ledcube import serializer


class Template():
    def __init__(self) -> None:
        self.__populated_data: Dict[str, Any] = dict()

    @property
    def populated_data(self) -> Dict[str, Any]:
        return deepcopy(self.__populated_data)

    def generate(self) -> bytes:
        try:
            raise NotImplementedError
        except KeyError:
            raise ValueError("Data was not populated!")

    def __len__(self) -> int:
        raise NotImplementedError

    @staticmethod
    def template() -> Dict[str, Any]:
        raise NotImplementedError


#### Frames ####################################################################
class Frame():
    @property
    def populated_data(self) -> Dict[str, Any]:
        raise NotImplementedError

    def __len__(self) -> int:
        raise NotImplementedError

class FrameV1(Frame):
    def __init__(self, duration: int, tlc_states: Sequence[Sequence[int]]) -> None:
        self.__populated_data: Dict[str, Any] = dict()
        self.populate(duration, tlc_states)

    @property
    def populated_data(self) -> Dict[str, Any]:
        return deepcopy(self.__populated_data)

    def populate(self, duration: int, tlc_states: Sequence[Sequence[int]]) -> None:
        data = self.template()
        data["frame"]["secondary_header"]["duration"] = duration
        data["frame"]["secondary_header"]["data_length"] = len(tlc_states) * 24
        data["frame"]["tlc_states"] = [{"state": s} for s in tlc_states]

        self.__populated_data = data

    def generate(self) -> bytes:
        try:
            return serializer.frame_frame.build(self.__populated_data)
        except KeyError:
            raise ValueError("Data was not populated!")

    def __len__(self) -> int:
        try:
            return serializer.primary_header_primary_header.sizeof() + serializer.frame_v1_secondary_header.sizeof() + self.__populated_data["frame"]["secondary_header"]["data_length"]
        except (SizeofError, KeyError):
            raise ValueError("Data was not populated!")

    @staticmethod
    def template() -> Dict[str, Any]:
        return {
            "primary_header": {
                "type": 0,
                "version": 1
            },
            "frame": {
                "secondary_header": {
                    "duration": None,
                    "data_length": None
                },
                "tlc_states": None
            }
        }


#### Animations ################################################################
class Animation():
    def __len__(self) -> int:
        raise NotImplementedError

class AnimationV1(Animation):
    def __init__(self, name: str, timestamp: int, tlc_count: int, frame_count: int, frames: Sequence[Frame]) -> None:
        self.__populated_data: Dict[str, Any] = dict()
        self.populate(name, timestamp, tlc_count, frame_count, frames)

    @property
    def populated_data(self) -> Dict[str, Any]:
        return deepcopy(self.__populated_data)

    def populate(self, name: str, timestamp: int, tlc_count: int, frame_count: int, frames: Sequence[Frame]) -> None:
        data = AnimationV1.template()
        data["animation"]["secondary_header"]["name"] = name
        data["animation"]["secondary_header"]["time"] = timestamp
        data["animation"]["secondary_header"]["tlc_count"] = tlc_count
        data["animation"]["secondary_header"]["frame_count"] = frame_count

        # Calculate data length
        data_length = 4  # 4 bytes for CRC
        data_length += sum((len(fr) for fr in frames))
        data["animation"]["secondary_header"]["data_length"] = data_length

        # Create frame data
        data["animation"]["frames"] = [f.populated_data for f in frames]

        # Generate CRC
        data["crc"] = crc32(serializer.animation_v1_animation_v1.build(data["animation"]))

        self.__populated_data = data

    def generate(self) -> bytes:
        try:
            return serializer.animation_animation.build(self.__populated_data)
        except KeyError:
            raise ValueError("Data was not populated!")

    @staticmethod
    def template() -> Dict[str, Any]:
        return {
        "primary_header": {
            "type": 1,
            "version": 1
        },
        "animation": {
            "secondary_header": {
                "name": None,
                "time": None,
                "tlc_count": None,
                "frame_count": None,
                "data_length": None
            },
            "frames": None
        },
        "crc": None,
    }

    @staticmethod
    def __len__() -> int:
        return serializer.animation_animation.sizeof()
