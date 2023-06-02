//
// Created by mike on 5/30/23.
//

#include "primaryheader.h"

namespace parser {
    // #### Private ####
    void PrimaryHeader::readData() {
        _card->fileSeek(_offset);

        uint8_t buf[1];
        if (_card->fileRead(buf, 1, nullptr))
            _type = buf[0];
        if (_card->fileRead(buf, 1, nullptr))
            _version = buf[0];
    }

    // #### Public ####
    // Constructor & Destructor
    PrimaryHeader::PrimaryHeader(SDCard *card, uint offset) {
        _offset = offset;
        _card = card;
        _size = 2;

        _type = 0;
        _version = 0;

        readData();
    }

    // Attributes
    uint8_t PrimaryHeader::type() const {
        return _type;
    }
    uint8_t PrimaryHeader::version() const {
        return _version;
    }

    // Functions
    bool PrimaryHeader::getPayload(uint index, uint8_t *buf) {
        return false;
    }

} // parser
