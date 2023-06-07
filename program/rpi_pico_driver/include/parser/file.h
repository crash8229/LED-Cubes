//
// Created by mike on 6/6/23.
//

#ifndef RPI_PICO_DRIVER_FILE_H
#define RPI_PICO_DRIVER_FILE_H

#include "parserbase.h"
#include "library.h"

namespace parser {

    class File: public ParserBase {
    private:
        // Variables

        // Attributes
        PrimaryHeader _primaryHeader = PrimaryHeader();

        // Functions
        void readData() override;
        bool getPayload(uint index, void *obj) override;

    public:
        // Constructor & Destructor
        File();
        File(SDCard *card, uint offset);

        // Variables

        // Attributes
        [[nodiscard]] uint8_t type() const;
        [[nodiscard]] uint8_t version() const;

        // Functions
        void init(SDCard *card, uint offset);
        [[nodiscard]] uint payloadSize(uint index) override;
        void getPayload(Library *library);

    };

} // parser

#endif //RPI_PICO_DRIVER_FILE_H
