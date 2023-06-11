//
// Created by mike on 6/2/23.
//

#include <stdexcept>
#include "frame.h"

namespace parser {
    // #### Private ####
    void Frame::readData() {
        _card->fileSeek(_offset);

        _primaryHeader.init(_card, _card->fileTell());
        if (_primaryHeader.type() != PrimaryHeader::type::FRAME)
            throw std::invalid_argument("Primary header did not match expected type of: FRAME");

        uint8_t buf[frameV1HeaderSize];
        if (_card->fileRead(buf, frameV1HeaderSize, nullptr)) {
            _duration = getUINT16(buf, 0);
            _dataLength = getUINT16(buf, 2);
        }

        _payloadOffset = _card->fileTell();
        _payloadSize = _numTLCs * bytesPerTLC;
        _payloadCount = _dataLength / _payloadSize;
    }
    bool Frame::getPayload(uint index, void *obj) {
        auto *buf = (uint8_t *) obj;

        if (index >= _payloadCount)
            throw std::out_of_range("");
        if (_payloadCurrentIndex != index)
            _card->fileSeek(_payloadOffset + _payloadSize * index);
        _payloadCurrentIndex = index + 1;
        uint bytesRead = 0;
        bool result = _card->fileRead(buf, _payloadSize, &bytesRead);
        return bytesRead == bytesPerTLC && result;
    }

    // #### Public ####
    // Constructor & Destructor
    Frame::Frame() = default;
    Frame::Frame(SDCard *card, uint offset, uint8_t numTLCs) {
        init(card, offset, numTLCs);
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
    void Frame::init(SDCard *card, uint offset, uint8_t numTLCs) {
        _offset = offset;
        _card = card;
        _numTLCs = numTLCs;
        readData();
        _size = _primaryHeader.size() + frameV1HeaderSize + _dataLength;
    }
    uint Frame::payloadSize(uint index) {
        return _payloadSize;
    }
    std::vector<uint8_t> Frame::getPayload(uint index) {
        std::vector<uint8_t> buf(_payloadSize);
        getPayload(index, (void *)&buf[0]);
        return buf;
    }

    Frame::FrameData Frame::getFrameData(uint index) {
        return {_duration, getPayload(index)};
    }

} // parser
