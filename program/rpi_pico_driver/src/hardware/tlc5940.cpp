//
// Created by mike on 11/28/21.
//

#include "tlc5940.h"
#include "pico/stdlib.h"

TLC5940::TLC5940() = default;

TLC5940::TLC5940(const spi_inst_t *port, uint8_t sclk, uint8_t mosi, uint8_t xlat, uint8_t blank, uint8_t gsclk,
                 uint8_t num) {
    init(port, sclk, mosi, xlat, blank, gsclk, num);
}

TLC5940::TLC5940(TLC5940Config *tlc_config) {
    init(tlc_config);
}

TLC5940::~TLC5940() {
    // Cleanup
    ledAllOff();

    gpio_put(cfg.tlcXlat, false);
    gpio_put(cfg.tlcBlank, true);
    gpio_put(cfg.tlcGsclk, false);

    gpio_deinit(cfg.tlcXlat);
    gpio_deinit(cfg.tlcBlank);
    gpio_deinit(cfg.tlcGsclk);

    spi_deinit((spi_inst_t *)cfg.spiPort);
    gpio_deinit(cfg.spiSclk);
    gpio_deinit(cfg.spiMosi);
}

// Private
/* ****************************************************************************************************************** */
void TLC5940::init() {
    gsOutData.reserve(cfg.tlcNum * GRAYSCALE_BYTE_SIZE);

    // Init GPIO
    gpio_init(cfg.tlcXlat);
    gpio_init(cfg.tlcBlank);
    gpio_init(cfg.tlcGsclk);
    gpio_set_dir(cfg.tlcXlat, GPIO_OUT);
    gpio_set_dir(cfg.tlcBlank, GPIO_OUT);
    gpio_set_dir(cfg.tlcGsclk, GPIO_OUT);

    // Init SPI
    spi_init((spi_inst_t *)cfg.spiPort, 1000 * 1000 * 30);  // 30MHz
    gpio_set_function(cfg.spiSclk, GPIO_FUNC_SPI);
    gpio_set_function(cfg.spiMosi, GPIO_FUNC_SPI);

    // Init all outputs to off
    ledAllOff();
}

// Public
/* ****************************************************************************************************************** */
void TLC5940::init(const spi_inst_t *port, uint8_t sclk, uint8_t mosi, uint8_t xlat, uint8_t blank, uint8_t gsclk,
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
    spi_write_blocking((spi_inst_t *)cfg.spiPort, outData, GRAYSCALE_BYTE_SIZE * cfg.tlcNum);

    gpio_put(cfg.tlcBlank, true);

    gpio_put(cfg.tlcXlat, true);
    gpio_put(cfg.tlcXlat, false);

    gpio_put(cfg.tlcBlank, false);

    gpio_put(cfg.tlcGsclk, true);
    gpio_put(cfg.tlcGsclk, false);
}

uint8_t *TLC5940::getRawGrayscale(const uint16_t *values) const {
    // Construct spi data
    int idx;
    for (int gs_idx = 0; gs_idx < GRAYSCALE_BYTE_SIZE * cfg.tlcNum; gs_idx = gs_idx + 3) {
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
    for (int gs_idx = 0; gs_idx < GRAYSCALE_BYTE_SIZE * cfg.tlcNum; gs_idx = gs_idx + 3) {
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
    gpio_put(cfg.tlcBlank, true);
    gpio_put(cfg.tlcBlank, false);
}

void TLC5940::setBlank(bool state) const {
    gpio_put(cfg.tlcBlank, state);
}

void TLC5940::xlatPulse() const {
    gpio_put(cfg.tlcXlat, true);
    gpio_put(cfg.tlcXlat, false);
}

void TLC5940::gsclkPulse() const {
    gpio_put(cfg.tlcGsclk, true);
    gpio_put(cfg.tlcGsclk, false);
}

void TLC5940::ledAllOff() {
    gsOutData.assign(GRAYSCALE_BYTE_SIZE * cfg.tlcNum, 0);
    setRawGrayscale(&gsOutData[0]);
}

void TLC5940::ledAllOn() {
    gsOutData.assign(GRAYSCALE_BYTE_SIZE * cfg.tlcNum, 1);
    setRawGrayscale(&gsOutData[0]);
}
