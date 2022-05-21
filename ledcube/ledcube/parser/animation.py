# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

from pkg_resources import parse_version
import kaitaistruct
from kaitaistruct import KaitaiStruct, KaitaiStream, BytesIO


if parse_version(kaitaistruct.__version__) < parse_version('0.9'):
    raise Exception("Incompatible Kaitai Struct Python API: 0.9 or later is required, but you have %s" % (kaitaistruct.__version__))

from ledcube.parser import animation_v1
from ledcube.parser import primary_header
class Animation(KaitaiStruct):
    """LED Cube animation."""
    def __init__(self, _io, _parent=None, _root=None):
        self._io = _io
        self._parent = _parent
        self._root = _root if _root else self
        self._read()

    def _read(self):
        self.primary_header = primary_header.PrimaryHeader(self._io)
        _on = self.primary_header.version
        if _on == 1:
            self.animation = animation_v1.AnimationV1(self._io)


