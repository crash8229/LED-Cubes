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
        PrimaryHeader _primaryHeader = PrimaryHeader();
        uint16_t _duration = 0;
        uint16_t _dataLength = 0;

        // Functions
        void readData() override;
        bool getPayload(uint index, void *obj) override;

    public:
        // Constructor & Destructor
        Frame();
        Frame(SDCard *card, uint offset, uint8_t numTLCs);

        // Variables
        static const uint8_t bytesPerTLC = 24;
        static const uint8_t frameV1HeaderSize = 4;

        // Attributes
        [[nodiscard]] uint8_t type() const;
        [[nodiscard]] uint8_t version() const;
        [[nodiscard]] uint16_t duration() const;
        [[nodiscard]] uint16_t dataLength() const;

        // Functions
        void init(SDCard *card, uint offset, uint8_t numTLCs);
        [[nodiscard]] uint payloadSize(uint index) override;
        bool getPayload(uint index, uint8_t *tlcStates);
    };

} // parser

#endif //RPI_PICO_DRIVER_FRAME_H
