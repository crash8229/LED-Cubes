// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "frame_v1.h"

frame_v1_t::frame_v1_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, frame_v1_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_secondary_header = 0;
    m_tlc_states = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void frame_v1_t::_read() {
    m_secondary_header = new secondary_header_t(m__io, this, m__root);
    m_tlc_states = new std::vector<tlc_t*>();
    const int l_tlc_states = (secondary_header()->data_length() / 24);
    for (int i = 0; i < l_tlc_states; i++) {
        m_tlc_states->push_back(new tlc_t(m__io, this, m__root));
    }
}

frame_v1_t::~frame_v1_t() {
    _clean_up();
}

void frame_v1_t::_clean_up() {
    if (m_secondary_header) {
        delete m_secondary_header; m_secondary_header = 0;
    }
    if (m_tlc_states) {
        for (std::vector<tlc_t*>::iterator it = m_tlc_states->begin(); it != m_tlc_states->end(); ++it) {
            delete *it;
        }
        delete m_tlc_states; m_tlc_states = 0;
    }
}

frame_v1_t::secondary_header_t::secondary_header_t(kaitai::kstream* p__io, frame_v1_t* p__parent, frame_v1_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void frame_v1_t::secondary_header_t::_read() {
    m_duration = m__io->read_u2be();
    m_data_length = m__io->read_u2be();
}

frame_v1_t::secondary_header_t::~secondary_header_t() {
    _clean_up();
}

void frame_v1_t::secondary_header_t::_clean_up() {
}

frame_v1_t::tlc_t::tlc_t(kaitai::kstream* p__io, frame_v1_t* p__parent, frame_v1_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_state = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void frame_v1_t::tlc_t::_read() {
    m_state = new std::vector<uint64_t>();
    const int l_state = 16;
    for (int i = 0; i < l_state; i++) {
        m_state->push_back(m__io->read_bits_int_be(12));
    }
}

frame_v1_t::tlc_t::~tlc_t() {
    _clean_up();
}

void frame_v1_t::tlc_t::_clean_up() {
    if (m_state) {
        delete m_state; m_state = 0;
    }
}
