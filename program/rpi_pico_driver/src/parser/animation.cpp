//
// Created by mike on 6/4/23.
//

#include <stdexcept>
#include "animation.h"

namespace parser {
    // #### Private ####
    void Animation::readData() {
        _card->fileSeek(_offset);

        _primaryHeader.init(_card, _card->fileTell());
        if (_primaryHeader.type() != PrimaryHeader::type::ANIMATION)
            throw std::invalid_argument("Primary header did not match expected type of: ANIMATION");

        uint8_t buf[animationV1HeaderSize];
        if (_card->fileRead(buf, animationV1HeaderSize, nullptr)) {
            getString(buf, 0, 32, _sha256);
            _sha256[32] = 0;
            getString(buf, 32, 32, _name);
            _name[32] = 0;
            _time = getUINT64(buf, 64);
            _frameCount = getUINT16(buf, 72);
            _dataLength = getUINT32(buf, 74);
        }

        _payloadOffset = _card->fileTell();
        _payloadSize = _primaryHeader.size() + Frame::frameV1HeaderSize + _numTLCs * parser::Frame::bytesPerTLC * _numLayers;
        _payloadCount = _frameCount;
    }
    uint64_t Animation::payloadSize(uint32_t index) {
        return _payloadSize;
    }
    bool Animation::getPayload(uint32_t index, void *obj) {
        auto *frame = (Frame *)obj;

        if (index >= _payloadCount)
            throw std::out_of_range("");
        if (_payloadCurrentIndex != index)
            _card->fileSeek(_payloadOffset + _payloadSize * index);
        _payloadCurrentIndex = index + 1;
        frame->init(_card, _card->fileTell(), _numTLCs);
        return true;
    }

    // #### Public ####
    // Constructor & Destructor
    Animation::Animation() = default;
    Animation::Animation(SDCard *card, uint64_t offset, uint8_t numTLCs, uint8_t numLayers) {
        init(card, offset, numTLCs, numLayers);
    }

    // Attributes
    uint8_t Animation::type() const {
        return _primaryHeader.type();
    }
    uint8_t Animation::version() const {
        return _primaryHeader.version();
    }
    std::string Animation::sha256() const {
        return getHexString((uint8_t *)_sha256, 0, 32);
    }
    std::string Animation::name() const {
        return {_name};
    }
    uint64_t Animation::time() const {
        return  _time;
    }
    uint16_t Animation::frameCount() const {
        return _frameCount;
    }
    uint32_t Animation::dataLength() const {
        return _dataLength;
    }

    // Functions
    void Animation::init(SDCard *card, uint64_t offset, uint8_t numTLCs, uint8_t numLayers) {
        _offset = offset;
        _card = card;
        _numTLCs = numTLCs;
        _numLayers = numLayers;
        readData();
        _size = _primaryHeader.size() + animationV1HeaderSize + _dataLength;
    }
    uint64_t Animation::payloadSize() {
        return payloadSize(0);
    }
    Frame Animation::getPayload(uint32_t index) {
        auto frame = Frame();
        getPayload(index, (void *)&frame);
        return frame;
    }

} // parser