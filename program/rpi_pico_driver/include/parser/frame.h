//
// Created by mike on 6/2/23.
//

#ifndef RPI_PICO_DRIVER_FRAME_H
#define RPI_PICO_DRIVER_FRAME_H

#include "primaryheader.h"

namespace parser {

    class Frame: public ParserBase{
    private:
        // Variables
        uint8_t _numTLCs = 0;
        uint8_t _numLayers = 0;

        // Attribute
        PrimaryHeader _primaryHeader = PrimaryHeader(nullptr, 0);
        uint16_t _duration = 0;
        uint16_t _dataLength = 0;

        // Functions
        void readData() override;

    public:
        // Constructor & Destructor
        Frame(SDCard *card, uint offset, uint8_t numTLCs, uint8_t numLayers);

        // Variables
        static const uint8_t bytesPerTLC = 24;

        // Attributes
        [[nodiscard]] uint8_t type() const;
        [[nodiscard]] uint8_t version() const;
        [[nodiscard]] uint16_t duration() const;
        [[nodiscard]] uint16_t dataLength() const;

        // Functions
        [[nodiscard]] uint payloadSize(uint index) const override;
        bool getPayload(uint index, uint8_t *buf) override;
    };

} // parser

#endif //RPI_PICO_DRIVER_FRAME_H
