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
        if (_primaryHeader.type() != PrimaryHeader::type::LIBRARY)
            throw std::invalid_argument("Primary header did not match expected type of: LIBRARY");

        uint8_t buf[libraryV1HeaderSize];
        if (_card->fileRead(buf, libraryV1HeaderSize, nullptr)) {
            _sha256 = hexStr(buf, 32, 0);
            _name = getString(buf, 32, 32);
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
    bool Library::getPayload(uint index, void *obj) {
        auto *animation = (Animation *)obj;

        if (index >= _payloadCount)
            throw std::out_of_range("");
        if (_payloadCurrentIndex != index) {
            _card->fileSeek(_payloadOffset);
            for (uint i = 0; i <= index; i++) {
                animation->init(_card, _card->fileTell(), _tlcCount, _zSize);
                if (i != index)
                    _card->fileSeek(_card->fileTell() + animation->dataLength());
            }
        }
        else
            animation->init(_card, _card->fileTell(), _tlcCount, _zSize);
        _payloadCurrentIndex = index + 1;
        return true;
    }

    // #### Public ####
    // Constructor & Destructor
    Library::Library() = default;
    Library::Library(SDCard *card, uint offset) {
        init(card, offset);
    }

    // Attributes
    uint8_t Library::type() const {
        return _primaryHeader.type();
    }
    uint8_t Library::version() const {
        return _primaryHeader.version();
    }
    std::string Library::sha256() const {
        return _sha256;
    }
    std::string Library::name() const {
        return _name;
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
    void Library::init(SDCard *card, uint offset) {
        _offset = offset;
        _card = card;
        readData();
        _size = _primaryHeader.size() + libraryV1HeaderSize + _dataLength;
    }
    uint Library::payloadSize(uint index) {
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
    void Library::getPayload(uint index, Animation *animation) {
        getPayload(index, (void *)animation);
    }

} // parser