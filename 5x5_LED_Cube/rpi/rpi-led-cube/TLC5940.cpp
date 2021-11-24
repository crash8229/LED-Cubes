//
// Created by Mike Umana on 9/20/2021.
//

#include "TLC5940.h"
#include <iostream>
#include <pigpio.h>
#include <algorithm>


TLC5940::TLC5940(uint8_t tlc, unsigned spi_ch, uint8_t xlat, uint8_t blank, uint8_t gsclk) {
    this->xlat = xlat;
    this->blank = blank;
    this->gsclk = gsclk;
    this->tlc = tlc;

    // Init data vectors
    gs_out_data.reserve(tlc * 24);

    // Init pigpio
    if (gpioInitialise() < 0)
        throw std::runtime_error("GPIO did not initialise!");

    // Init GPIO
    gpioSetMode(xlat, PI_OUTPUT);
    gpioSetMode(blank, PI_OUTPUT);
    gpioSetMode(gsclk, PI_OUTPUT);

    gpioWrite(xlat, 0);
    gpioWrite(blank, 0);
    gpioWrite(gsclk, 0);

    // Init SPI
    spi = spiOpen(spi_ch, 17000000, 0b0000000000000000000000);

    // Set Init Grayscale
    std::vector<char> vals;
    vals.assign(24 * tlc, 0);
    char* values = &vals[0];
    setRawGrayscale(values);
}

TLC5940::~TLC5940() {
    std::vector<char> vals;
    vals.assign(24 * tlc, 0);
    char* values = &vals[0];
    setRawGrayscale(values);

    // Cleanup
    gpioWrite(xlat, 0);
    gpioWrite(blank, 0);
    gpioWrite(gsclk, 0);

    spiClose(spi);

    gpioTerminate();
}

void TLC5940::sleep(struct timespec sleep_time) {
    while (nanosleep(&sleep_time, &sleep_time));
}

void TLC5940::setRawGrayscale(char* spi_data) const {
    // Set Grayscale
    spiWrite(spi, spi_data, 24 * tlc);
    gpioWrite(blank, 1);
    gpioWrite(xlat, 1);
    gpioWrite(xlat, 0);
    gpioWrite(blank, 0);
    gpioWrite(gsclk, 1);
    gpioWrite(gsclk, 0);
}

void TLC5940::setGrayscale(const uint16_t* values) const {
    // Construct spi data
    int idx;
    for (int gs_idx = 0; gs_idx < 24 * tlc; gs_idx = gs_idx + 3) {
        idx = gs_idx - gs_idx/3;
        gs_out_data[gs_idx] = (values[idx] & 0b111111110000) >> 4;
        gs_out_data[gs_idx + 1] = (values[idx] & 0b1111) << 4 | (values[idx + 1] & 0b111100000000) >> 8;
        gs_out_data[gs_idx + 2] = values[idx + 1];
    }

    // Set Grayscale
    char* spi_data = &gs_out_data[0];
    setRawGrayscale(spi_data);
}

void TLC5940::setGrayscale(const char* values) const {
    // Construct spi data
    int idx;
    for (int gs_idx = 0; gs_idx < 24 * tlc; gs_idx = gs_idx + 3) {
        idx = gs_idx - gs_idx/3;
        gs_out_data[gs_idx] = (values[idx] & 0b11110000) >> 4;
        gs_out_data[gs_idx + 1] = (values[idx] & 0b1111) << 4;
        gs_out_data[gs_idx + 2] = values[idx + 1];
    }

    // Set Grayscale
    char* spi_data = &gs_out_data[0];
    setRawGrayscale(spi_data);
}
