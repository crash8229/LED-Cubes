//
// Created by mike on 6/2/23.
//

#ifndef RPI_PICO_DRIVER_PARSERBASE_H
#define RPI_PICO_DRIVER_PARSERBASE_H

#include "sdcard.h"

namespace parser {

    class ParserBase {
    protected:
        // Variables
        SDCard *_card = nullptr;
        uint _offset = 0;
        uint _size = 0;
        uint _payloadOffset = 0;
        uint _payloadCount = 0;
        uint _payloadSize = 0;
        uint _payloadCurrentIndex = 0;

        // Functions
        virtual void readData() = 0;

    public:
        // Constructor & Destructor

        // Functions
        SDCard *card();
        [[nodiscard]] uint size() const;
        [[nodiscard]] uint offset() const;
        [[nodiscard]] uint payloadOffset() const;
        [[nodiscard]] uint payloadCount() const;
        [[nodiscard]] virtual uint payloadSize(uint index) const = 0;
        virtual bool getPayload(uint index, uint8_t *buf) = 0;

    };

} // parser

#endif //RPI_PICO_DRIVER_PARSERBASE_H
