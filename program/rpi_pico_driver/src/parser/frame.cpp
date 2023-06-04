//
// Created by mike on 6/2/23.
//

#include <stdexcept>
#include "frame.h"

namespace parser {
    // #### Private ####
    void Frame::readData() {
        _card->fileSeek(_offset);

        _primaryHeader = PrimaryHeader(_card, _card->fileTell());
        if (_primaryHeader.type() != PrimaryHeader::type::FRAME)
            throw std::invalid_argument("Primary header did not match expected type of: FRAME");

        uint8_t buf[4];
        uint bytesRead = 0;
        if (_card->fileRead(buf, 4, &bytesRead)) {
            _duration = buf[0] << 8 | buf[1];
            _dataLength = buf[2] << 8 | buf[3];
        }

        _payloadOffset = _card->fileTell();
        _payloadSize = _numTLCs * _numLayers * bytesPerTLC;
        _payloadCount = _dataLength / _payloadSize;
    }

    // #### Public ####
    // Constructor & Destructor
    Frame::Frame(SDCard *card, uint offset, uint8_t numTLCs, uint8_t numLayers) {
        _offset = offset;
        _card = card;
        _numTLCs = numTLCs;
        _numLayers = numLayers;
        readData();
        _size = _primaryHeader.size() + 4 + _dataLength;
    }

    // Attributes
    uint8_t Frame::type() const {
        return _primaryHeader.type();
    }
    uint8_t Frame::version() const {
        return _primaryHeader.version();
    }
    uint16_t Frame::duration() const {
        return _duration;
    }
    uint16_t Frame::dataLength() const {
        return _dataLength;
    }

    // Functions
    uint Frame::payloadSize(uint index) const {
        return _payloadSize;
    }
    bool Frame::getPayload(uint index, uint8_t *buf) {
        if (_payloadCurrentIndex != index) {
            _card->fileSeek(_payloadOffset + bytesPerTLC * index);
        }
        _payloadCurrentIndex = index + 1;
        uint bytesRead = 0;
        bool result = _card->fileRead(buf, _payloadSize, &bytesRead);
        return bytesRead == bytesPerTLC && result;
    }

} // parser