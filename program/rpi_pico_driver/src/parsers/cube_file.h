#ifndef CUBE_FILE_H_
#define CUBE_FILE_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include "primary_header.h"
#include "library.h"

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif
namespace led_cube_file {
    class primary_header_t;
    class library_t;

    /**
     * LED Cube file
     */

    class cube_file_t : public kaitai::kstruct {

    public:

        cube_file_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, cube_file_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~cube_file_t();

    private:
        primary_header_t* m_primary_header;
        library_t* m_file;
        bool n_file;

    public:
        bool _is_null_file() { file(); return n_file; };

    private:
        cube_file_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        primary_header_t* primary_header() const { return m_primary_header; }

        /**
         * The structure is determined by the version
         */
        library_t* file() const { return m_file; }
        cube_file_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };
}

#endif  // CUBE_FILE_H_
