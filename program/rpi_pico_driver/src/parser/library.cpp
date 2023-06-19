//
// Created by mike on 6/6/23.
//

#include <stdexcept>
#include "library.h"

namespace parser {
    // #### Private ####
    void Library::readData() {
        _card->fileSeek(_offset);

        _primaryHeader.init(_card, _card->fileTell());
        if (_primaryHeader.type() != PrimaryHeader::Type::LIBRARY)
            throw std::invalid_argument("Primary header did not match expected type of: LIBRARY");

        uint8_t buf[libraryV1HeaderSize];
        if (_card->fileRead(buf, libraryV1HeaderSize, nullptr)) {
            getString(buf, 0, 32, _sha256);
            _sha256[32] = 0;
            getString(buf, 32, 32, _name);
            _name[32] = 0;
            _time = getUINT64(buf, 64);
            _xSize = buf[72];
            _ySize = buf[73];
            _zSize = buf[74];
            _tlcCount = buf[75];
            _animationCount = buf[76];
            _dataLength = getUINT64(buf, 77);
        }

        _payloadOffset = _card->fileTell();
        _payloadCount = _animationCount;
        _payloadCurrentIndex = 1;
        _payloadSize = payloadSize(0);
    }
    bool Library::getPayload(uint32_t index, void *obj) {
        auto *animation = (Animation *)obj;

        if (index >= _payloadCount)
            throw std::out_of_range("");
        if (_payloadCurrentIndex != index) {
            setPayloadIndex(index);
        }
        animation->init(_card, _card->fileTell(), _tlcCount, _zSize);
        _payloadCurrentIndex = index + 1;
        return true;
    }

    // #### Public ####
    // Constructor & Destructor
    Library::Library() = default;
    Library::Library(SDCard *card, uint64_t offset) {
        init(card, offset);
    }

    // Attributes
    PrimaryHeader::Type Library::type() const {
        return _primaryHeader.type();
    }
    uint8_t Library::version() const {
        return _primaryHeader.version();
    }
    std::string Library::sha256() const {
        return getHexString((uint8_t *)_sha256, 0, 32);
    }
    std::string Library::name() const {
        return {_name};
    }
    uint64_t Library::time() const {
        return  _time;
    }
    uint8_t Library::xSize() const {
        return _xSize;
    }
    uint8_t Library::ySize() const {
        return _ySize;
    }
    uint8_t Library::zSize() const {
        return _zSize;
    }
    uint8_t Library::tlcCount() const {
        return _tlcCount;
    }
    uint8_t Library::animationCount() const {
        return _animationCount;
    }
    uint64_t Library::dataLength() const {
        return _dataLength;
    }

    // Functions
    void Library::init(SDCard *card, uint64_t offset) {
        _offset = offset;
        _card = card;
        readData();
        _size = _primaryHeader.size() + libraryV1HeaderSize + _dataLength;
    }
    uint64_t Library::payloadSize(uint32_t index) {
        Animation animation = Animation();
        if (index >= _payloadCount)
            throw std::out_of_range("");
        if (_payloadCurrentIndex != index) {
            _card->fileSeek(_payloadOffset);
            uint currentAnimationOffset = _card->fileTell();
            for (uint i = 0; i <= index; i++) {
                animation.init(_card, currentAnimationOffset, _tlcCount, _zSize);
                if (i != index)
                    currentAnimationOffset = _card->fileTell() + animation.dataLength();
            }
            _payloadSize = animation.size();
            _payloadCurrentIndex = index;
            _card->fileSeek(currentAnimationOffset);
        }
        return _payloadSize;
    }
    Animation Library::getPayload(uint32_t index) {
        auto animation = Animation();
        getPayload(index, (void *)&animation);
        return animation;
    }
    void Library::setPayloadIndex(uint32_t index) {
        Animation animation = Animation();

        _card->fileSeek(_payloadOffset);
        for (uint i = 0; i < index; i++) {
            animation.init(_card, _card->fileTell(), _tlcCount, _zSize);
            if (i != index)
                _card->fileSeek(_card->fileTell() + animation.dataLength());
        }
        _payloadCurrentIndex = index;
    }
} // parser
