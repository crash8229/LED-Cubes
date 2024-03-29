//
// Created by mike on 6/4/23.
//

#ifndef RPI_PICO_DRIVER_ANIMATION_H
#define RPI_PICO_DRIVER_ANIMATION_H

#include <string>
#include "primaryheader.h"
#include "frame.h"

namespace parser {

    class Animation: public ParserBase {
    private:
        // Variables
        uint8_t _numTLCs = 0;
        uint8_t _numLayers = 0;

        // Attribute
        PrimaryHeader _primaryHeader = PrimaryHeader();
        char _sha256[33]{};
        char _name[33]{};
        uint64_t _time = 0;
        uint16_t _frameCount = 0;
        uint32_t _dataLength = 0;

        // Functions
        void readData() override;
        [[nodiscard]] uint64_t payloadSize(uint32_t index) override;
        bool getPayload(uint32_t index, void *obj) override;

    public:
        // Constructor & Destructor
        Animation();
        Animation(SDCard *card, uint64_t offset, uint8_t numTLCs, uint8_t numLayers);

        // Variables
        static const uint8_t animationV1HeaderSize = 78;

        // Structs
        typedef struct {
            char name[sizeof(_name)];
            uint64_t time;
            uint16_t frameCount;
            uint64_t size;
        } AnimationInfo;

        // Attributes
        [[nodiscard]] PrimaryHeader::Type type() const;
        [[nodiscard]] uint8_t version() const;
        [[nodiscard]] std::string sha256() const;
        [[nodiscard]] std::string name() const;
        [[nodiscard]] uint64_t time() const;
        [[nodiscard]] uint16_t frameCount() const;
        [[nodiscard]] uint32_t dataLength() const;

        // Functions
        void init(SDCard *card, uint64_t offset, uint8_t numTLCs, uint8_t numLayers);
        [[nodiscard]] uint64_t payloadSize();
        Frame getPayload(uint32_t index);
        void setPayloadIndex(uint32_t index) override;
        AnimationInfo getInfo();
    };

} // parser

#endif //RPI_PICO_DRIVER_ANIMATION_H
