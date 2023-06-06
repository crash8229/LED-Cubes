//
// Created by mike on 5/30/23.
//

#ifndef RPI_PICO_DRIVER_PRIMARYHEADER_H
#define RPI_PICO_DRIVER_PRIMARYHEADER_H

#include "parserbase.h"

namespace parser {

class PrimaryHeader: public ParserBase{
    private:
        // Attributes
        uint8_t _type = 0;
        uint8_t _version = 0;

        // Functions
        void readData() override;
        [[nodiscard]] uint payloadSize(uint index) const override;
        bool getPayload(uint index, void *obj) override;

    public:
        // Constructor & Destructor
        PrimaryHeader();
        PrimaryHeader(SDCard *card, uint offset);

        // Enums
        enum type {
            FRAME,
            ANIMATION,
            LIBRARY,
            FILE
        };

        // Attributes
        [[nodiscard]] uint8_t type() const;
        [[nodiscard]] uint8_t version() const;

        // Functions
        void init(SDCard *card, uint offset);
};

} // parser

#endif //RPI_PICO_DRIVER_PRIMARYHEADER_H
