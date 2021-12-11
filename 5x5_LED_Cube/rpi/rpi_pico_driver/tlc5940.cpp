#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"
#pragma ide diagnostic ignored "modernize-deprecated-headers"
//
// Created by mike on 11/28/21.
//


#include "tlc5940.h"
#include "pico/stdlib.h"

TLC5940::TLC5940(const TLC5940Config *tlc_config) {
    // Init class variables
    cfg = tlc_config;
    gs_out_data.reserve(cfg->tlc_num * 24);

    // Init GPIO
    gpio_init(cfg->tlc_xlat);
    gpio_init(cfg->tlc_blank);
    gpio_init(cfg->tlc_gsclk);
    gpio_set_dir(cfg->tlc_xlat, GPIO_OUT);
    gpio_set_dir(cfg->tlc_blank, GPIO_OUT);
    gpio_set_dir(cfg->tlc_gsclk, GPIO_OUT);

    // Init SPI
    spi_init(cfg->spi_port, 1000 * 1000 * 30);  // 30MHz
    gpio_set_function(cfg->spi_miso, GPIO_FUNC_SPI);
    gpio_set_function(cfg->spi_cs, GPIO_FUNC_SIO);
    gpio_set_function(cfg->spi_sck, GPIO_FUNC_SPI);
    gpio_set_function(cfg->spi_mosi, GPIO_FUNC_SPI);
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(cfg->spi_cs, GPIO_OUT);
    gpio_put(cfg->spi_cs, 1);

    // Init all outputs to off
    ledAllOff();
}

TLC5940::~TLC5940() {
    // Cleanup
    ledAllOff();

    gpio_put(cfg->tlc_xlat, 0);
    gpio_put(cfg->tlc_blank, 0);
    gpio_put(cfg->tlc_gsclk, 0);

    spi_deinit(cfg->spi_port);
}

void TLC5940::setRawGrayscale(uint8_t *out_data) const {
    // Set Grayscale
    spi_write_blocking(cfg->spi_port, out_data, 24 * cfg->tlc_num);

    gpio_put(cfg->tlc_blank, 1);

    gpio_put(cfg->tlc_xlat, 1);
    gpio_put(cfg->tlc_xlat, 0);

    gpio_put(cfg->tlc_blank, 0);

    gpio_put(cfg->tlc_gsclk, 1);
    gpio_put(cfg->tlc_gsclk, 0);
}

uint8_t *TLC5940::getRawGrayscale(const uint16_t *values) const {
    // Construct spi data
    int idx;
    for (int gs_idx = 0; gs_idx < 24 * cfg->tlc_num; gs_idx = gs_idx + 3) {
        idx = gs_idx - gs_idx / 3;
        gs_out_data[gs_idx] = (values[idx] & 0b111111110000) >> 4;
        gs_out_data[gs_idx + 1] = (values[idx] & 0b1111) << 4 | (values[idx + 1] & 0b111100000000) >> 8;
        gs_out_data[gs_idx + 2] = values[idx + 1];
    }

    return &gs_out_data[0];
}

void TLC5940::setGrayscale(const uint16_t *values) const {
    setRawGrayscale(getRawGrayscale(values));
}

uint8_t *TLC5940::getRawGrayscale(const uint8_t *values) const {
    // Construct spi data
    int idx;
    for (int gs_idx = 0; gs_idx < 24 * cfg->tlc_num; gs_idx = gs_idx + 3) {
        idx = gs_idx - gs_idx / 3;
        gs_out_data[gs_idx] = (values[idx] & 0b11110000) >> 4;
        gs_out_data[gs_idx + 1] = (values[idx] & 0b1111) << 4;
        gs_out_data[gs_idx + 2] = values[idx + 1];
    }

    return &gs_out_data[0];
}

void TLC5940::setGrayscale(const uint8_t *values) const {
    setRawGrayscale(getRawGrayscale(values));
}

void TLC5940::blankPulse() {
    gpio_put(cfg->tlc_blank, 1);
    gpio_put(cfg->tlc_blank, 0);
}

void TLC5940::setBlank(bool state) {
    gpio_put(cfg->tlc_blank, state);
}

void TLC5940::xlatPulse() {
    gpio_put(cfg->tlc_xlat, 1);
    gpio_put(cfg->tlc_xlat, 0);
}

void TLC5940::gsclkPulse() {
    gpio_put(cfg->tlc_gsclk, 1);
    gpio_put(cfg->tlc_gsclk, 0);
}

void TLC5940::ledAllOff() {
    gs_out_data.assign(24 * cfg->tlc_num, 0);
    setRawGrayscale(&gs_out_data[0]);
}

#pragma clang diagnostic pop
