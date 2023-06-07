//
// Created by mike on 6/6/23.
//

#ifndef RPI_PICO_DRIVER_LIBRARY_H
#define RPI_PICO_DRIVER_LIBRARY_H

#include <string>
#include "primaryheader.h"
#include "animation.h"

namespace parser {

    class Library: public ParserBase {
    private:
        // Variables

        // Attributes
        PrimaryHeader _primaryHeader = PrimaryHeader();
        std::string _sha256;
        std::string _name;
        uint64_t _time = 0;
        uint8_t  _xSize = 0;
        uint8_t  _ySize = 0;
        uint8_t  _zSize = 0;
        uint8_t _tlcCount = 0;
        uint8_t _animationCount = 0;
        uint64_t _dataLength = 0;

        // Functions
        void readData() override;
        bool getPayload(uint index, void *obj) override;

    public:
        // Constructor & Destructor
        Library();
        Library(SDCard *card, uint offset);

        // Variables
        static const uint8_t libraryV1HeaderSize = 85;

        // Attributes
        [[nodiscard]] uint8_t type() const;
        [[nodiscard]] uint8_t version() const;
        [[nodiscard]] std::string sha256() const;
        [[nodiscard]] std::string name() const;
        [[nodiscard]] uint64_t time() const;
        [[nodiscard]] uint8_t  xSize() const;
        [[nodiscard]] uint8_t  ySize() const;
        [[nodiscard]] uint8_t  zSize() const;
        [[nodiscard]] uint8_t tlcCount() const;
        [[nodiscard]] uint8_t animationCount() const;
        [[nodiscard]] uint64_t dataLength() const;

        // Functions
        void init(SDCard *card, uint offset);
        [[nodiscard]] uint payloadSize(uint index) override;
        void getPayload(uint index, Animation *animation);
    };

} // parser

#endif //RPI_PICO_DRIVER_LIBRARY_H
