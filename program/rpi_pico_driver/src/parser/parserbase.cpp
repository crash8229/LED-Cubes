//
// Created by mike on 5/30/23.
//

#include "parserbase.h"

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
