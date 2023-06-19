//
// Created by mike on 6/2/23.
//

#ifndef RPI_PICO_DRIVER_FRAME_H
#define RPI_PICO_DRIVER_FRAME_H

#include <vector>
#include "primaryheader.h"

namespace parser {

    class Frame: public ParserBase{
    private:
        // Variables
        uint8_t _numTLCs = 0;

        // Attribute
        PrimaryHeader _primaryHeader = PrimaryHeader();
        uint16_t _duration = 0;
        uint16_t _dataLength = 0;

        // Functions
        void readData() override;
        [[nodiscard]] uint64_t payloadSize(uint32_t index) override;
        bool getPayload(uint32_t index, void *obj) override;

    public:
        // Constructor & Destructor
        Frame();
        Frame(SDCard *card, uint64_t offset, uint8_t numTLCs);

        // Variables
        static const uint8_t bytesPerTLC = 24;
        static const uint8_t frameV1HeaderSize = 4;

        // Structs
        typedef struct {
            uint16_t duration;
            std::vector<uint8_t> tlcStates;
        } FrameData;

        // Attributes
        [[nodiscard]] PrimaryHeader::Type type() const;
        [[nodiscard]] uint8_t version() const;
        [[nodiscard]] uint16_t duration() const;
        [[nodiscard]] uint16_t dataLength() const;

        // Functions
        void init(SDCard *card, uint64_t offset, uint8_t numTLCs);
        [[nodiscard]] uint64_t payloadSize();
        std::vector<uint8_t> getPayload(uint32_t index);
        void setPayloadIndex(uint32_t index) override;
        FrameData getFrameData();
    };

} // parser

#endif //RPI_PICO_DRIVER_FRAME_H
