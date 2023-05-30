#ifndef FRAME_V1_H_
#define FRAME_V1_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

/**
 * Version 1 of the frame specification
 */

class frame_v1_t : public kaitai::kstruct {

public:
    class secondary_header_t;
    class tlc_t;

    frame_v1_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, frame_v1_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~frame_v1_t();

    /**
     * Houses the frame duration and data length
     */

    class secondary_header_t : public kaitai::kstruct {

    public:

        secondary_header_t(kaitai::kstream* p__io, frame_v1_t* p__parent = 0, frame_v1_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~secondary_header_t();

    private:
        uint16_t m_duration;
        uint16_t m_data_length;
        frame_v1_t* m__root;
        frame_v1_t* m__parent;

    public:

        /**
         * How long to display the frame in ms
         */
        uint16_t duration() const { return m_duration; }

        /**
         * Number of bytes after the header
         */
        uint16_t data_length() const { return m_data_length; }
        frame_v1_t* _root() const { return m__root; }
        frame_v1_t* _parent() const { return m__parent; }
    };

    /**
     * LED states for a single TLC 5940
     */

    class tlc_t : public kaitai::kstruct {

    public:

        tlc_t(kaitai::kstream* p__io, frame_v1_t* p__parent = 0, frame_v1_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~tlc_t();

    private:
        std::vector<uint64_t>* m_state;
        frame_v1_t* m__root;
        frame_v1_t* m__parent;

    public:
        std::vector<uint64_t>* state() const { return m_state; }
        frame_v1_t* _root() const { return m__root; }
        frame_v1_t* _parent() const { return m__parent; }
    };

private:
    secondary_header_t* m_secondary_header;
    std::vector<tlc_t*>* m_tlc_states;
    frame_v1_t* m__root;
    kaitai::kstruct* m__parent;

public:
    secondary_header_t* secondary_header() const { return m_secondary_header; }
    std::vector<tlc_t*>* tlc_states() const { return m_tlc_states; }
    frame_v1_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // FRAME_V1_H_
