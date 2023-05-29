// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "primary_header.h"
namespace led_cube_file {

    primary_header_t::primary_header_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, primary_header_t* p__root) : kaitai::kstruct(p__io) {
        m__parent = p__parent;
        m__root = this;

        try {
            _read();
        } catch(...) {
            _clean_up();
            throw;
        }
    }

    void primary_header_t::_read() {
        m_type = static_cast<primary_header_t::type_t>(m__io->read_u1());
        m_version = m__io->read_u1();
    }

    primary_header_t::~primary_header_t() {
        _clean_up();
    }

    void primary_header_t::_clean_up() {
    }
}
