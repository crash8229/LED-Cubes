#ifndef PRIMARY_HEADER_H_
#define PRIMARY_HEADER_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif
namespace led_cube_file {

    /**
     * Used in all objects to specify the type and version
     */

    class primary_header_t : public kaitai::kstruct {

    public:

        enum type_t {
            TYPE_FRAME = 0,
            TYPE_ANIMATION = 1,
            TYPE_LIBRARY = 2,
            TYPE_FILE = 3
        };

        primary_header_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, primary_header_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~primary_header_t();

    private:
        type_t m_type;
        uint8_t m_version;
        primary_header_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        type_t type() const { return m_type; }
        uint8_t version() const { return m_version; }
        primary_header_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };
}

#endif  // PRIMARY_HEADER_H_
