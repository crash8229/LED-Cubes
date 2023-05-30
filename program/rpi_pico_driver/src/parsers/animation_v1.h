#ifndef ANIMATION_V1_H_
#define ANIMATION_V1_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include "frame.h"
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif
class frame_t;

/**
 * Version 1 of the animation specification
 */

class animation_v1_t : public kaitai::kstruct {

public:
    class secondary_header_t;

    animation_v1_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, animation_v1_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~animation_v1_t();

    /**
     * Houses the animation metadata
     */

    class secondary_header_t : public kaitai::kstruct {

    public:

        secondary_header_t(kaitai::kstream* p__io, animation_v1_t* p__parent = 0, animation_v1_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~secondary_header_t();

    private:
        std::string m_name;
        uint64_t m_time;
        uint16_t m_frame_count;
        uint32_t m_data_length;
        animation_v1_t* m__root;
        animation_v1_t* m__parent;

    public:

        /**
         * Name of the animation
         */
        std::string name() const { return m_name; }

        /**
         * UNIX timestamp of file creation
         */
        uint64_t time() const { return m_time; }

        /**
         * Number of frames in the animation
         */
        uint16_t frame_count() const { return m_frame_count; }

        /**
         * Number of bytes after the header
         */
        uint32_t data_length() const { return m_data_length; }
        animation_v1_t* _root() const { return m__root; }
        animation_v1_t* _parent() const { return m__parent; }
    };

private:
    secondary_header_t* m_secondary_header;
    std::vector<frame_t*>* m_frames;
    animation_v1_t* m__root;
    kaitai::kstruct* m__parent;

public:
    secondary_header_t* secondary_header() const { return m_secondary_header; }
    std::vector<frame_t*>* frames() const { return m_frames; }
    animation_v1_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // ANIMATION_V1_H_
