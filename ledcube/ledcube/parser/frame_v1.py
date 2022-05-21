# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

from pkg_resources import parse_version
import kaitaistruct
from kaitaistruct import KaitaiStruct, KaitaiStream, BytesIO


if parse_version(kaitaistruct.__version__) < parse_version('0.9'):
    raise Exception("Incompatible Kaitai Struct Python API: 0.9 or later is required, but you have %s" % (kaitaistruct.__version__))

class FrameV1(KaitaiStruct):
    """Version 1 of the frame specification."""
    def __init__(self, _io, _parent=None, _root=None):
        self._io = _io
        self._parent = _parent
        self._root = _root if _root else self
        self._read()

    def _read(self):
        self.secondary_header = FrameV1.SecondaryHeader(self._io, self, self._root)
        self.tlc_states = [None] * (self.secondary_header.data_length // 24)
        for i in range(self.secondary_header.data_length // 24):
            self.tlc_states[i] = FrameV1.Tlc(self._io, self, self._root)


    class SecondaryHeader(KaitaiStruct):
        """Houses the frame duration and data length."""
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.duration = self._io.read_u2be()
            self.data_length = self._io.read_u2be()


    class Tlc(KaitaiStruct):
        """LED states for a single TLC 5940."""
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.state = [None] * (16)
            for i in range(16):
                self.state[i] = self._io.read_bits_int_be(12)




