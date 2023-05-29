// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "frame.h"
namespace led_cube_file {

    frame_t::frame_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, frame_t* p__root) : kaitai::kstruct(p__io) {
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

    void frame_t::_read() {
        m_primary_header = new primary_header_t(m__io);
        n_frame = true;
        switch (primary_header()->version()) {
        case 1: {
            n_frame = false;
            m_frame = new frame_v1_t(m__io);
            break;
        }
        }
    }

    frame_t::~frame_t() {
        _clean_up();
    }

    void frame_t::_clean_up() {
        if (m_primary_header) {
            delete m_primary_header; m_primary_header = 0;
        }
        if (!n_frame) {
            if (m_frame) {
                delete m_frame; m_frame = 0;
            }
        }
    }
}
