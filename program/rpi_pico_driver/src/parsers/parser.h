#ifndef PARSER_H_
#define PARSER_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include "primary_header.h"
#include "animation.h"
#include "library.h"
#include "frame.h"
#include "cube_file.h"

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif
namespace led_cube_file {
    class primary_header_t;
    class animation_t;
    class library_t;
    class frame_t;
    class cube_file_t;

    /**
     * LED Cube Master Parser
     * This parser looks at the primary header to determine how to parse the data
     * provided. This parser is the recommended method to process data related to the
     * LED Cube specification.
     */

    class parser_t : public kaitai::kstruct {

    public:

        parser_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, parser_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~parser_t();

    private:
        bool f_object;
        kaitai::kstruct* m_object;
        bool n_object;

    public:
        bool _is_null_object() { object(); return n_object; };

    private:

    public:

        /**
         * This is where the data is actually parsed
         */
        kaitai::kstruct* object();

    private:
        primary_header_t* m_primary_header;
        parser_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        primary_header_t* primary_header() const { return m_primary_header; }
        parser_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };
}

#endif  // PARSER_H_
