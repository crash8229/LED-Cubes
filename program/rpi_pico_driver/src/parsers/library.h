#ifndef LIBRARY_H_
#define LIBRARY_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include "library_v1.h"
#include "primary_header.h"

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif
namespace led_cube_file {
    class library_v1_t;
    class primary_header_t;

    /**
     * LED Cube library
     */

    class library_t : public kaitai::kstruct {

    public:

        library_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, library_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~library_t();

    private:
        primary_header_t* m_primary_header;
        std::string m_sha256;
        library_v1_t* m_library;
        bool n_library;

    public:
        bool _is_null_library() { library(); return n_library; };

    private:
        library_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        primary_header_t* primary_header() const { return m_primary_header; }

        /**
         * SHA256 of the contents in library
         */
        std::string sha256() const { return m_sha256; }

        /**
         * The structure is determined by the version
         */
        library_v1_t* library() const { return m_library; }
        library_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };
}

#endif  // LIBRARY_H_
