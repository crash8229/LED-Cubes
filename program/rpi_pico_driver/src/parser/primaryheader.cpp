//
// Created by mike on 5/30/23.
//

#include "primaryheader.h"

namespace parser {
    // #### Private ####
    void PrimaryHeader::readData() {
        _card->fileSeek(_offset);

        uint8_t buf[2];
        if (_card->fileRead(buf, 2, nullptr)) {
            _type = buf[0];
            _version = buf[1];
        }
    }
    uint PrimaryHeader::payloadSize(uint index) const {
        return 0;
    }
    bool PrimaryHeader::getPayload(uint index, void *obj) {
        return false;
    }

    // #### Public ####
    // Constructor & Destructor
    PrimaryHeader::PrimaryHeader() = default;
    PrimaryHeader::PrimaryHeader(SDCard *card, uint offset) {
        init(card, offset);
    }

    // Attributes
    uint8_t PrimaryHeader::type() const {
        return _type;
    }
    uint8_t PrimaryHeader::version() const {
        return _version;
    }

    // Functions
    void PrimaryHeader::init(SDCard *card, uint offset) {
        _offset = offset;
        _card = card;
        _size = 2;
        readData();
    }

} // parser
