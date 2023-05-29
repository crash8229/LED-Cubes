// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "library_v1.h"
namespace led_cube_file {

    library_v1_t::library_v1_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, library_v1_t* p__root) : kaitai::kstruct(p__io) {
        m__parent = p__parent;
        m__root = this;
        m_secondary_header = 0;
        m_animations = 0;

        try {
            _read();
        } catch(...) {
            _clean_up();
            throw;
        }
    }

    void library_v1_t::_read() {
        m_secondary_header = new secondary_header_t(m__io, this, m__root);
        m_animations = new std::vector<animation_t*>();
        const int l_animations = secondary_header()->animation_count();
        for (int i = 0; i < l_animations; i++) {
            m_animations->push_back(new animation_t(m__io));
        }
    }

    library_v1_t::~library_v1_t() {
        _clean_up();
    }

    void library_v1_t::_clean_up() {
        if (m_secondary_header) {
            delete m_secondary_header; m_secondary_header = 0;
        }
        if (m_animations) {
            for (std::vector<animation_t*>::iterator it = m_animations->begin(); it != m_animations->end(); ++it) {
                delete *it;
            }
            delete m_animations; m_animations = 0;
        }
    }

    library_v1_t::secondary_header_t::secondary_header_t(kaitai::kstream* p__io, library_v1_t* p__parent, library_v1_t* p__root) : kaitai::kstruct(p__io) {
        m__parent = p__parent;
        m__root = p__root;

        try {
            _read();
        } catch(...) {
            _clean_up();
            throw;
        }
    }

    void library_v1_t::secondary_header_t::_read() {
        m_name = kaitai::kstream::bytes_to_str(m__io->read_bytes(32), std::string("UTF-8"));
        m_time = m__io->read_u8be();
        m_x_size = m__io->read_u1();
        m_y_size = m__io->read_u1();
        m_z_size = m__io->read_u1();
        m_tlc_count = m__io->read_u1();
        m_animation_count = m__io->read_u1();
        m_data_length = m__io->read_u8be();
    }

    library_v1_t::secondary_header_t::~secondary_header_t() {
        _clean_up();
    }

    void library_v1_t::secondary_header_t::_clean_up() {
    }
}
