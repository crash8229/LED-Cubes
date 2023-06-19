//
// Created by mike on 5/30/23.
//

#include "primaryheader.h"

namespace parser {
    // #### Private ####
    void PrimaryHeader::readData() {
        _card->fileSeek(_offset);

        uint8_t buf[_size];
        if (_card->fileRead(buf, _size, nullptr)) {
            _type = static_cast<enum Type>(buf[0]);
            _version = buf[1];
        }
    }
    uint64_t PrimaryHeader::payloadSize(uint32_t index) {
        return 0;
    }
    bool PrimaryHeader::getPayload(uint32_t index, void *obj) {
        return false;
    }
    void PrimaryHeader::setPayloadIndex(uint32_t index) {}

    // #### Public ####
    // Constructor & Destructor
    PrimaryHeader::PrimaryHeader() = default;
    PrimaryHeader::PrimaryHeader(SDCard *card, uint64_t offset) {
        init(card, offset);
    }

    // Attributes
    PrimaryHeader::Type PrimaryHeader::type() const {
        return _type;
    }
    uint8_t PrimaryHeader::version() const {
        return _version;
    }

    // Functions
    void PrimaryHeader::init(SDCard *card, uint64_t offset) {
        _offset = offset;
        _card = card;
        _size = 2;
        readData();
    }
} // parser
