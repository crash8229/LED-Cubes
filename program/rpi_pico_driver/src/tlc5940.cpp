#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"
#pragma ide diagnostic ignored "modernize-deprecated-headers"
//
// Created by mike on 11/28/21.
//


#include "tlc5940.h"
#include "pico/stdlib.h"

TLC5940::TLC5940() = default;

TLC5940::TLC5940(spi_inst_t *port, uint sclk, uint mosi, uint xlat, uint blank, uint gsclk,
                 uint8_t num) {
    init(port, sclk, mosi, xlat, blank, gsclk, num);
}

TLC5940::TLC5940(TLC5940Config *tlc_config) {
    init(tlc_config);
}

TLC5940::~TLC5940() {
    // Cleanup
    ledAllOff();

    gpio_put(cfg.tlcXlat, 0);
    gpio_put(cfg.tlcBlank, 1);
    gpio_put(cfg.tlcGsclk, 0);

    gpio_deinit(cfg.tlcXlat);
    gpio_deinit(cfg.tlcBlank);
    gpio_deinit(cfg.tlcGsclk);

    spi_deinit(cfg.spiPort);
    gpio_deinit(cfg.spiSclk);
    gpio_deinit(cfg.spiMosi);
}

// Private
/* ****************************************************************************************************************** */
void TLC5940::init() {
    gsOutData.reserve(cfg.tlcNum * GRAYSCALE_BIT_SIZE);

    // Init GPIO
    gpio_init(cfg.tlcXlat);
    gpio_init(cfg.tlcBlank);
    gpio_init(cfg.tlcGsclk);
    gpio_set_dir(cfg.tlcXlat, GPIO_OUT);
    gpio_set_dir(cfg.tlcBlank, GPIO_OUT);
    gpio_set_dir(cfg.tlcGsclk, GPIO_OUT);

    // Init SPI
    spi_init(cfg.spiPort, 1000 * 1000 * 30);  // 30MHz
    gpio_set_function(cfg.spiSclk, GPIO_FUNC_SPI);
    gpio_set_function(cfg.spiMosi, GPIO_FUNC_SPI);

    // Init all outputs to off
    ledAllOff();
}

// Public
/* ****************************************************************************************************************** */
void TLC5940::init(spi_inst_t *port, uint sclk, uint mosi, uint xlat, uint blank, uint gsclk,
                   uint8_t num) {
    // Init class variables
    cfg = {
            port,
            sclk,
            mosi,
            num,
            xlat,
            blank,
            gsclk
    };

    init();
}

void TLC5940::init(TLC5940Config *tlc_config) {
    // Init class variables
    cfg = *tlc_config;

    init();
}

const TLC5940Config *TLC5940::getConfig() {
    return &cfg;
}

void TLC5940::setRawGrayscale(uint8_t *outData) const {
    // Set Grayscale
    spi_write_blocking(cfg.spiPort, outData, GRAYSCALE_BIT_SIZE * cfg.tlcNum);

    gpio_put(cfg.tlcBlank, 1);

    gpio_put(cfg.tlcXlat, 1);
    gpio_put(cfg.tlcXlat, 0);

    gpio_put(cfg.tlcBlank, 0);

    gpio_put(cfg.tlcGsclk, 1);
    gpio_put(cfg.tlcGsclk, 0);
}

uint8_t *TLC5940::getRawGrayscale(const uint16_t *values) const {
    // Construct spi data
    int idx;
    for (int gs_idx = 0; gs_idx < GRAYSCALE_BIT_SIZE * cfg.tlcNum; gs_idx = gs_idx + 3) {
        idx = gs_idx - gs_idx / 3;
        gsOutData[gs_idx] = (values[idx] & 0b111111110000) >> 4;
        gsOutData[gs_idx + 1] = (values[idx] & 0b1111) << 4 | (values[idx + 1] & 0b111100000000) >> 8;
        gsOutData[gs_idx + 2] = values[idx + 1];
    }

    return &gsOutData[0];
}

void TLC5940::setGrayscale(const uint16_t *values) const {
    setRawGrayscale(getRawGrayscale(values));
}

uint8_t *TLC5940::getRawGrayscale(const uint8_t *values) const {
    // Construct spi data
    int idx;
    for (int gs_idx = 0; gs_idx < GRAYSCALE_BIT_SIZE * cfg.tlcNum; gs_idx = gs_idx + 3) {
        idx = gs_idx - gs_idx / 3;
        gsOutData[gs_idx] = (values[idx] & 0b11110000) >> 4;
        gsOutData[gs_idx + 1] = (values[idx] & 0b1111) << 4;
        gsOutData[gs_idx + 2] = values[idx + 1];
    }

    return &gsOutData[0];
}

void TLC5940::setGrayscale(const uint8_t *values) const {
    setRawGrayscale(getRawGrayscale(values));
}

void TLC5940::blankPulse() const {
    gpio_put(cfg.tlcBlank, 1);
    gpio_put(cfg.tlcBlank, 0);
}

void TLC5940::setBlank(bool state) const {
    gpio_put(cfg.tlcBlank, state);
}

void TLC5940::xlatPulse() const {
    gpio_put(cfg.tlcXlat, 1);
    gpio_put(cfg.tlcXlat, 0);
}

void TLC5940::gsclkPulse() const {
    gpio_put(cfg.tlcGsclk, 1);
    gpio_put(cfg.tlcGsclk, 0);
}

void TLC5940::ledAllOff() {
    gsOutData.assign(GRAYSCALE_BIT_SIZE * cfg.tlcNum, 0);
    setRawGrayscale(&gsOutData[0]);
}

#pragma clang diagnostic pop
