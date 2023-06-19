//
// Created by mike on 6/6/23.
//

#include <stdexcept>
#include "file.h"

namespace parser {
    // #### Private ####
    void File::readData() {
        _card->fileSeek(_offset);

        _primaryHeader.init(_card, _card->fileTell());
        if (_primaryHeader.type() != PrimaryHeader::Type::FILE)
            throw std::invalid_argument("Primary header did not match expected type of: FILE");

        _payloadOffset = _card->fileTell();
        _payloadCount = 1;
        _payloadSize = _card->fileSize() - _primaryHeader.size();
    }
    uint64_t File::payloadSize(uint32_t index) {
        return _payloadSize;
    }
    bool File::getPayload(uint32_t index, void *obj) {
        auto *library = (Library *)obj;
        library->init(_card, _payloadOffset);
        return true;
    }
    void File::setPayloadIndex(uint32_t index) {}

    // #### Public ####
    // Constructor & Destructor
    File::File() = default;
    File::File(SDCard *card, uint64_t offset) {
        init(card, offset);
    }

    // Attributes
    PrimaryHeader::Type File::type() const {
        return _primaryHeader.type();
    }
    uint8_t File::version() const {
        return _primaryHeader.version();
    }

    // Functions
    void File::init(SDCard *card, uint64_t offset) {
        _offset = offset;
        _card = card;
        readData();
        _size = _primaryHeader.size() + _payloadSize;
    }
    uint64_t File::payloadSize() {
        return payloadSize(0);
    }
    Library File::getPayload() {
        auto library = Library();
        getPayload(0, (void *)&library);
        return library;
    }
} // parser
