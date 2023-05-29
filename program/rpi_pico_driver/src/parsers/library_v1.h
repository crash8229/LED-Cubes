#ifndef LIBRARY_V1_H_
#define LIBRARY_V1_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include "animation.h"
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif
namespace led_cube_file {
    class animation_t;

    /**
     * Version 1 of the library specification
     */

    class library_v1_t : public kaitai::kstruct {

    public:
        class secondary_header_t;

        library_v1_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, library_v1_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~library_v1_t();

        /**
         * Houses the library metadata
         */

        class secondary_header_t : public kaitai::kstruct {

        public:

            secondary_header_t(kaitai::kstream* p__io, library_v1_t* p__parent = 0, library_v1_t* p__root = 0);

        private:
            void _read();
            void _clean_up();

        public:
            ~secondary_header_t();

        private:
            std::string m_name;
            uint64_t m_time;
            uint8_t m_x_size;
            uint8_t m_y_size;
            uint8_t m_z_size;
            uint8_t m_tlc_count;
            uint8_t m_animation_count;
            uint64_t m_data_length;
            library_v1_t* m__root;
            library_v1_t* m__parent;

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
             * Number of LEDs along the X axis
             */
            uint8_t x_size() const { return m_x_size; }

            /**
             * Number of LEDs along the Y axis
             */
            uint8_t y_size() const { return m_y_size; }

            /**
             * Number of LEDs along the Z axis
             */
            uint8_t z_size() const { return m_z_size; }

            /**
             * Number of TLC 5940 chained together
             */
            uint8_t tlc_count() const { return m_tlc_count; }

            /**
             * Number of animations in the library
             */
            uint8_t animation_count() const { return m_animation_count; }

            /**
             * Number of bytes after the header
             */
            uint64_t data_length() const { return m_data_length; }
            library_v1_t* _root() const { return m__root; }
            library_v1_t* _parent() const { return m__parent; }
        };

    private:
        secondary_header_t* m_secondary_header;
        std::vector<animation_t*>* m_animations;
        library_v1_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        secondary_header_t* secondary_header() const { return m_secondary_header; }
        std::vector<animation_t*>* animations() const { return m_animations; }
        library_v1_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };
}

#endif  // LIBRARY_V1_H_
