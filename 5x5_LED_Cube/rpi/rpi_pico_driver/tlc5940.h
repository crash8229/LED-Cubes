//
// Created by mike on 11/28/21.
//

#ifndef RPIPICODRIVER_TLC5940_H
#define RPIPICODRIVER_TLC5940_H

#include <vector>
#include "hardware/spi.h"

typedef struct TLC5940Config {
    // SPI
    spi_inst_t *spi_port;
    uint spi_miso;
    uint spi_cs;
    uint spi_sclk;
    uint spi_mosi;

    // TLC5940 specific
    uint8_t tlc_num;
    uint tlc_xlat;
    uint tlc_blank;
    uint tlc_gsclk;
} TLC5940Config;

class TLC5940 {
private:
    TLC5940Config cfg{};
    mutable std::vector<uint8_t> gs_out_data;
    void init();

public:
    TLC5940(spi_inst_t *port, uint miso, uint cs, uint sclk, uint mosi, uint xlat, uint blank, uint gsclk, uint8_t num);
    explicit TLC5940(TLC5940Config *tlc_config);

    ~TLC5940();

    const TLC5940Config *getConfig();

    void setRawGrayscale(uint8_t *out_data) const;

    uint8_t *getRawGrayscale(const uint16_t *valueds) const;

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
