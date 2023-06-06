//
// Created by mike on 6/4/23.
//

#include <stdexcept>
#include "frame.h"
#include "animation.h"

namespace parser {
    // #### Private ####
    void Animation::readData() {
        _card->fileSeek(_offset);

        _primaryHeader = PrimaryHeader(_card, _card->fileTell());
        if (_primaryHeader.type() != PrimaryHeader::type::ANIMATION)
            throw std::invalid_argument("Primary header did not match expected type of: ANIMATION");

        uint8_t buf[78];
        uint bytesRead = 0;
        if (_card->fileRead(buf, 78, &bytesRead)) {
            _sha256 = std::string((char *)buf).substr(0, 32);
            _name = std::string((char *)buf).substr(32, 32);
            _time = getUINT64(buf, 64);
            _frameCount = getUINT16(buf, 72);
            _dataLength = getUINT32(buf, 74);
        }

        _payloadOffset = _card->fileTell();
        _payloadSize = _primaryHeader.size() + 4 + _numTLCs * parser::Frame::bytesPerTLC * _numLayers;
        _payloadCount = _dataLength / _payloadSize;
    }
    bool Animation::getPayload(uint index, void *obj) {
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
    Animation::Animation(SDCard *card, uint offset, uint8_t numTLCs, uint8_t numLayers) {
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
        return _sha256;
    }
    std::string Animation::name() const {
        return _name;
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
    void Animation::init(SDCard *card, uint offset, uint8_t numTLCs, uint8_t numLayers) {
        _offset = offset;
        _card = card;
        _numTLCs = numTLCs;
        _numLayers = numLayers;
        readData();
        _size = _primaryHeader.size() + 78 + _dataLength;
    }
    uint Animation::payloadSize(uint index) const {
        return _payloadSize;
    }
    void Animation::getPayload(uint index, Frame *frame) {
        getPayload(index, (void *)frame);
    }

} // parser