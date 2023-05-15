//
// Created by mike on 11/28/21.
//

#ifndef RPIPICODRIVER_TLC5940_H
#define RPIPICODRIVER_TLC5940_H

#include <vector>
#include "hardware/spi.h"

typedef struct TLC5940Config {
    // SPI
    spi_inst_t *spiPort;
    uint spiSclk;
    uint spiMosi;

    // TLC5940 specific
    uint8_t tlcNum;
    uint tlcXlat;
    uint tlcBlank;
    uint tlcGsclk;
} TLC5940Config;

class TLC5940 {
private:
    TLC5940Config cfg{};
    mutable std::vector<uint8_t> gsOutData;
    void init();

public:
    // Constructor & Destructor
    TLC5940();
    TLC5940(spi_inst_t *port, uint sclk, uint mosi, uint xlat, uint blank, uint gsclk, uint8_t num);
    explicit TLC5940(TLC5940Config *tlc_config);
    ~TLC5940();

    // Constants
    const uint8_t GRAYSCALE_BIT_SIZE = 24;

    // Functions
    void init(spi_inst_t *port, uint sclk, uint mosi, uint xlat, uint blank, uint gsclk, uint8_t num);
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
};

#endif //RPIPICODRIVER_TLC5940_H
