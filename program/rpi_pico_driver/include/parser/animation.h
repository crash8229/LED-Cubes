//
// Created by mike on 6/4/23.
//

#ifndef RPI_PICO_DRIVER_ANIMATION_H
#define RPI_PICO_DRIVER_ANIMATION_H

#include <string>
#include "primaryheader.h"
#include "frame.h"

namespace parser {

    class Animation: public ParserBase {
    private:
        // Variables
        uint8_t _numTLCs = 0;
        uint8_t _numLayers = 0;

        // Attribute
        PrimaryHeader _primaryHeader = PrimaryHeader();
        std::string _sha256;
        std::string _name;
        uint64_t _time = 0;
        uint16_t _frameCount = 0;
        uint32_t _dataLength = 0;

        // Functions
        void readData() override;
        bool getPayload(uint index, void *obj) override;

    public:
        // Constructor & Destructor
        Animation();
        Animation(SDCard *card, uint offset, uint8_t numTLCs, uint8_t numLayers);

        // Variables
        static const uint8_t animationV1HeaderSize = 78;

        // Attributes
        [[nodiscard]] uint8_t type() const;
        [[nodiscard]] uint8_t version() const;
        [[nodiscard]] std::string sha256() const;
        [[nodiscard]] std::string name() const;
        [[nodiscard]] uint64_t time() const;
        [[nodiscard]] uint16_t frameCount() const;
        [[nodiscard]] uint32_t dataLength() const;

        // Functions
        void init(SDCard *card, uint offset, uint8_t numTLCs, uint8_t numLayers);
        [[nodiscard]] uint payloadSize(uint index) override;
        void getPayload(uint index, Frame *frame);
    };

} // parser

#endif //RPI_PICO_DRIVER_ANIMATION_H
