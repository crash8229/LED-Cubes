// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "cube_file.h"
namespace led_cube_file {

    cube_file_t::cube_file_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, cube_file_t* p__root) : kaitai::kstruct(p__io) {
        m__parent = p__parent;
        m__root = this;
        m_primary_header = 0;

        try {
            _read();
        } catch(...) {
            _clean_up();
            throw;
        }
    }

    void cube_file_t::_read() {
        m_primary_header = new primary_header_t(m__io);
        n_file = true;
        switch (primary_header()->version()) {
        case 1: {
            n_file = false;
            m_file = new library_t(m__io);
            break;
        }
        }
    }

    cube_file_t::~cube_file_t() {
        _clean_up();
    }

    void cube_file_t::_clean_up() {
        if (m_primary_header) {
            delete m_primary_header; m_primary_header = 0;
        }
        if (!n_file) {
            if (m_file) {
                delete m_file; m_file = 0;
            }
        }
    }
}
