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
        if (_primaryHeader.type() != PrimaryHeader::type::FILE)
            throw std::invalid_argument("Primary header did not match expected type of: FILE");

        _payloadOffset = _card->fileTell();
        _payloadCount = 1;
        _payloadSize = _card->fileSize() - _primaryHeader.size();
    }
    bool File::getPayload(uint index, void *obj) {
        auto *library = (Library *)obj;
        library->init(_card, _payloadOffset);
        return true;
    }

    // #### Public ####
    // Constructor & Destructor
    File::File() = default;
    File::File(SDCard *card, uint offset) {
        init(card, offset);
    }

    // Attributes
    uint8_t File::type() const {
        return _primaryHeader.type();
    }
    uint8_t File::version() const {
        return _primaryHeader.version();
    }

    // Functions
    void File::init(SDCard *card, uint offset) {
        _offset = offset;
        _card = card;
        readData();
        _size = _primaryHeader.size() + _payloadSize;
    }
    uint File::payloadSize(uint index) {
        return _payloadSize;
    }
    void File::getPayload(Library *library) {
        getPayload(0, (void *)library);
    }

} // parser
