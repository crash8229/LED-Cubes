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
        static uint16_t getUINT16(const uint8_t *arr, uint offset);
        static uint32_t getUINT32(const uint8_t *arr, uint offset);
        static uint64_t getUINT64(const uint8_t *arr, uint offset);
        static std::string getString(const uint8_t *arr, uint offset, uint length);
        static std::string hexStr(uint8_t *data, uint32_t len, uint offset = 0);
        SDCard *card();
        [[nodiscard]] uint size() const;
        [[nodiscard]] uint offset() const;
        [[nodiscard]] uint payloadOffset() const;
        [[nodiscard]] uint payloadCount() const;
        [[nodiscard]] virtual uint payloadSize(uint index) = 0;
        virtual bool getPayload(uint index, void *obj) = 0;

    };

} // parser

#endif //RPI_PICO_DRIVER_PARSERBASE_H
