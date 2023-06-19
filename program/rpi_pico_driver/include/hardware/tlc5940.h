//
// Created by mike on 11/28/21.
//

#ifndef RPIPICODRIVER_TLC5940_H
#define RPIPICODRIVER_TLC5940_H

#include <vector>
#include "hardware/spi.h"

typedef struct TLC5940Config {
    // SPI
    const spi_inst_t *spiPort;
    uint8_t spiSclk;
    uint8_t spiMosi;

    // TLC5940 specific
    uint8_t tlcNum;
    uint8_t tlcXlat;
    uint8_t tlcBlank;
    uint8_t tlcGsclk;
} TLC5940Config;

class TLC5940 {
private:
    // Variables
    TLC5940Config cfg{};
    mutable std::vector<uint8_t> gsOutData;

    // Functions
    void init();

public:
    // Constructor & Destructor
    TLC5940();
    TLC5940(const spi_inst_t *port, uint8_t sclk, uint8_t mosi, uint8_t xlat, uint8_t blank, uint8_t gsclk, uint8_t num);
    explicit TLC5940(TLC5940Config *tlc_config);
    ~TLC5940();

    // Constants
    static const uint8_t GRAYSCALE_BYTE_SIZE = 24;

    // Functions
    void init(const spi_inst_t *port, uint8_t sclk, uint8_t mosi, uint8_t xlat, uint8_t blank, uint8_t gsclk, uint8_t num);
    void init(TLC5940Config *tlc_config);
    const TLC5940Config *getConfig();
    void setRawGrayscale(uint8_t *outData) const;
    uint8_t *getRawGrayscale(const uint16_t *values) const;
    void setGrayscale(const uint16_t *values) const;
    uint8_t *getRawGrayscale(const uint8_t *values) const;
    void setGrayscale(const uint8_t *values) const;
    void blankPulse() const;
    void setBlank(bool state) const;
    void xlatPulse() const;
    void gsclkPulse() const;
    void ledAllOff();
    void ledAllOn();
};

#endif //RPIPICODRIVER_TLC5940_H
