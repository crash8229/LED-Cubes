//
// Created by mike on 5/30/23.
//

#ifndef RPI_PICO_DRIVER_PRIMARYHEADER_H
#define RPI_PICO_DRIVER_PRIMARYHEADER_H

#include "sdcard.h"
#include "parserbase.h"

namespace parser {

class PrimaryHeader: public ParserBase{
    private:
        // Attributes
        uint8_t _type;
        uint8_t _version;

        // Functions
        void readData() override;

    public:
        // Constructor & Destructor
        PrimaryHeader(SDCard *sdcard, uint offset);

        // Attributes
        [[nodiscard]] uint8_t type() const;
        [[nodiscard]] uint8_t version() const;

        // Functions
        bool getPayload(uint index, uint8_t *buf) override;
};

} // parser

#endif //RPI_PICO_DRIVER_PRIMARYHEADER_H
