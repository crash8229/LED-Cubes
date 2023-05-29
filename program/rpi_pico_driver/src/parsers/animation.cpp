// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "animation.h"
namespace led_cube_file {

    animation_t::animation_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, animation_t* p__root) : kaitai::kstruct(p__io) {
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

    void animation_t::_read() {
        m_primary_header = new primary_header_t(m__io);
        m_sha256 = m__io->read_bytes(32);
        n_animation = true;
        switch (primary_header()->version()) {
        case 1: {
            n_animation = false;
            m_animation = new animation_v1_t(m__io);
            break;
        }
        }
    }

    animation_t::~animation_t() {
        _clean_up();
    }

    void animation_t::_clean_up() {
        if (m_primary_header) {
            delete m_primary_header; m_primary_header = 0;
        }
        if (!n_animation) {
            if (m_animation) {
                delete m_animation; m_animation = 0;
            }
        }
    }
}
