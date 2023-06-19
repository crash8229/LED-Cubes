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
        uint64_t _offset = 0;
        uint64_t _size = 0;
        uint64_t _payloadOffset = 0;
        uint32_t _payloadCount = 0;
        uint64_t _payloadSize = 0;
        uint32_t _payloadCurrentIndex = 0;

        // Functions
        virtual void readData() = 0;

    public:
        // Constructor & Destructor

        // Functions
        static uint16_t getUINT16(const uint8_t *arr, uint offset);
        static uint32_t getUINT32(const uint8_t *arr, uint offset);
        static uint64_t getUINT64(const uint8_t *arr, uint offset);
        static std::string getString(const uint8_t *arr, uint offset, uint length);
        static std::string getHexString(const uint8_t *data, uint offset, uint length);
        static void getString(const uint8_t *arr, uint offset, uint length, char *result);
        SDCard *card();
        [[nodiscard]] uint64_t size() const;
        [[nodiscard]] uint64_t offset() const;
        [[nodiscard]] uint64_t payloadOffset() const;
        [[nodiscard]] uint32_t payloadCount() const;
        [[nodiscard]] uint32_t payloadCurrentIndex() const;
        [[nodiscard]] virtual uint64_t payloadSize(uint32_t index) = 0;
        virtual bool getPayload(uint32_t index, void *obj) = 0;
        virtual void setPayloadIndex(uint32_t index) = 0;
    };

} // parser

#endif //RPI_PICO_DRIVER_PARSERBASE_H
