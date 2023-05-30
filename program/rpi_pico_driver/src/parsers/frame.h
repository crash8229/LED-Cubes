#ifndef FRAME_H_
#define FRAME_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include "primary_header.h"
#include "frame_v1.h"

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif
class primary_header_t;
class frame_v1_t;

/**
 * Single animation frame
 */

class frame_t : public kaitai::kstruct {

public:

    frame_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, frame_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~frame_t();

private:
    primary_header_t* m_primary_header;
    frame_v1_t* m_frame;
    bool n_frame;

public:
    bool _is_null_frame() { frame(); return n_frame; };

private:
    frame_t* m__root;
    kaitai::kstruct* m__parent;

public:
    primary_header_t* primary_header() const { return m_primary_header; }

    /**
     * The structure is determined by the version
     */
    frame_v1_t* frame() const { return m_frame; }
    frame_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // FRAME_H_
