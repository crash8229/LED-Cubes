// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "animation_v1.h"

animation_v1_t::animation_v1_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, animation_v1_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_secondary_header = 0;
    m_frames = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void animation_v1_t::_read() {
    m_secondary_header = new secondary_header_t(m__io, this, m__root);
    m_frames = new std::vector<frame_t*>();
    const int l_frames = secondary_header()->frame_count();
    for (int i = 0; i < l_frames; i++) {
        m_frames->push_back(new frame_t(m__io));
    }
}

animation_v1_t::~animation_v1_t() {
    _clean_up();
}

void animation_v1_t::_clean_up() {
    if (m_secondary_header) {
        delete m_secondary_header; m_secondary_header = 0;
    }
    if (m_frames) {
        for (std::vector<frame_t*>::iterator it = m_frames->begin(); it != m_frames->end(); ++it) {
            delete *it;
        }
        delete m_frames; m_frames = 0;
    }
}

animation_v1_t::secondary_header_t::secondary_header_t(kaitai::kstream* p__io, animation_v1_t* p__parent, animation_v1_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void animation_v1_t::secondary_header_t::_read() {
    m_name = kaitai::kstream::bytes_to_str(m__io->read_bytes(32), std::string("UTF-8"));
    m_time = m__io->read_u8be();
    m_frame_count = m__io->read_u2be();
    m_data_length = m__io->read_u4be();
}

animation_v1_t::secondary_header_t::~secondary_header_t() {
    _clean_up();
}

void animation_v1_t::secondary_header_t::_clean_up() {
}
