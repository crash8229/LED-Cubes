// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "parser.h"

parser_t::parser_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, parser_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_primary_header = 0;
    f_object = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void parser_t::_read() {
    m_primary_header = new primary_header_t(m__io);
}

parser_t::~parser_t() {
    _clean_up();
}

void parser_t::_clean_up() {
    if (m_primary_header) {
        delete m_primary_header; m_primary_header = 0;
    }
    if (f_object && !n_object) {
        if (m_object) {
            delete m_object; m_object = 0;
        }
    }
}

kaitai::kstruct* parser_t::object() {
    if (f_object)
        return m_object;
    std::streampos _pos = m__io->pos();
    m__io->seek(0);
    n_object = true;
    switch (primary_header()->type()) {
    case primary_header_t::TYPE_FRAME: {
        n_object = false;
        m_object = new frame_t(m__io);
        break;
    }
    case primary_header_t::TYPE_ANIMATION: {
        n_object = false;
        m_object = new animation_t(m__io);
        break;
    }
    case primary_header_t::TYPE_LIBRARY: {
        n_object = false;
        m_object = new library_t(m__io);
        break;
    }
    case primary_header_t::TYPE_FILE: {
        n_object = false;
        m_object = new cube_file_t(m__io);
        break;
    }
    }
    m__io->seek(_pos);
    f_object = true;
    return m_object;
}
