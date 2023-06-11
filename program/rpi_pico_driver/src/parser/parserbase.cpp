//
// Created by mike on 5/30/23.
//

#include "parserbase.h"
#include <iomanip>

namespace parser {
    // #### Private ####

    // #### Public ####
    // Constructor & Destructor

    // Functions

    uint16_t ParserBase::getUINT16(const uint8_t *arr, uint offset) {
        return arr[offset] << 8 | arr[offset + 1];
    }
    uint32_t ParserBase::getUINT32(const uint8_t *arr, uint offset) {
        return (uint32_t)getUINT16(arr, offset) << 16 | getUINT16(arr, offset + 2);
    }
    uint64_t ParserBase::getUINT64(const uint8_t *arr, uint offset) {
        return (uint64_t)getUINT32(arr, offset) << 32 | getUINT32(arr, offset + 4);
    }
    std::string ParserBase::getString(const uint8_t *arr, uint offset, uint length) {
        std::stringstream ss;

        for( uint i = offset ; i < length + offset; ++i )
            ss << (char)arr[i];

        return ss.str();
    }
    std::string ParserBase::getHexString(const uint8_t *data, uint offset, uint length) {
        std::stringstream ss;
        ss << std::hex;

        for(uint i = offset ; i < length + offset; ++i )
            ss << std::setw(2) << std::setfill('0') << (int)data[i];

        return ss.str();
    }
    SDCard *ParserBase::card() {
        return _card;
    }
    uint ParserBase::size() const {
        return _size;
    }
    uint ParserBase::offset() const {
        return _offset;
    }
    uint ParserBase::payloadOffset() const {
        return _payloadOffset;
    }
    uint ParserBase::payloadCount() const {
        return _payloadCount;
    }

} // parser
