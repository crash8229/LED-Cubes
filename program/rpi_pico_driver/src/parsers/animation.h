#ifndef ANIMATION_H_
#define ANIMATION_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include "animation_v1.h"
#include "primary_header.h"

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif
class animation_v1_t;
class primary_header_t;

/**
 * LED Cube animation
 */

class animation_t : public kaitai::kstruct {

public:

    animation_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, animation_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~animation_t();

private:
    primary_header_t* m_primary_header;
    std::string m_sha256;
    animation_v1_t* m_animation;
    bool n_animation;

public:
    bool _is_null_animation() { animation(); return n_animation; };

private:
    animation_t* m__root;
    kaitai::kstruct* m__parent;

public:
    primary_header_t* primary_header() const { return m_primary_header; }

    /**
     * SHA256 of the contents in animation
     */
    std::string sha256() const { return m_sha256; }

    /**
     * The structure is determined by the version
     */
    animation_v1_t* animation() const { return m_animation; }
    animation_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // ANIMATION_H_
