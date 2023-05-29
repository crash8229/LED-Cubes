// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "library.h"
namespace led_cube_file {

    library_t::library_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, library_t* p__root) : kaitai::kstruct(p__io) {
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

    void library_t::_read() {
        m_primary_header = new primary_header_t(m__io);
        m_sha256 = m__io->read_bytes(32);
        n_library = true;
        switch (primary_header()->version()) {
        case 1: {
            n_library = false;
            m_library = new library_v1_t(m__io);
            break;
        }
        }
    }

    library_t::~library_t() {
        _clean_up();
    }

    void library_t::_clean_up() {
        if (m_primary_header) {
            delete m_primary_header; m_primary_header = 0;
        }
        if (!n_library) {
            if (m_library) {
                delete m_library; m_library = 0;
            }
        }
    }
}
