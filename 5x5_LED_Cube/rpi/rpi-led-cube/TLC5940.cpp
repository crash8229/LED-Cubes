//
// Created by Mike Umana on 9/20/2021.
//

#include "TLC5940.h"
#include <iostream>
#include <pigpio.h>

TLC5940::TLC5940(unsigned spi_ch, uint8_t xlat, uint8_t blank, uint8_t gsclk) {
    this->xlat = xlat;
    this->blank = blank;
    this->gsclk = gsclk;

    // Init pigpio
    if (gpioInitialise() < 0)
        std::cout << "GPIO did not initialise!" << std::endl;

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
    uint16_t gs_values[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    setGrayscale(gs_values);
}

TLC5940::~TLC5940() {
    setLEDs(0);

    // Cleanup
    gpioWrite(xlat, 0);
    gpioWrite(blank, 0);
    gpioWrite(gsclk, 0);

    spiClose(spi);

    gpioTerminate();
}

void TLC5940::setGrayscale(const uint16_t *values) const {
    char grayscale_data[24];
    uint16_t rvalues[16];

    int j;
    for (int i = 15; i >= 0; i--) {
        j = 15 - i;
        rvalues[j] = values[i];
    }

    int idx;
    for (int gs_idx = 0; gs_idx < 24; gs_idx = gs_idx + 3) {
        idx = gs_idx - gs_idx/3;
        grayscale_data[gs_idx] = (rvalues[idx] & 0b111111110000) >> 4;
        grayscale_data[gs_idx + 1] = (rvalues[idx] & 0b1111) << 4 | (rvalues[idx + 1] & 0b111100000000) >> 8;
        grayscale_data[gs_idx + 2] = rvalues[idx + 1];
    }

    // Set Grayscale
    spiWrite(spi, grayscale_data, 24);
    gpioWrite(blank, 1);
//    gpioTrigger(xlat, 1, 1);
    gpioWrite(xlat, 1);
    gpioWrite(xlat, 0);
    gpioWrite(blank, 0);
}

void TLC5940::setLEDs(const uint16_t states) const {
    uint16_t values[16];
    for (int i = 0; i < 16; i++) {
        if ((states >> i) & 1) {
            values[i] = 4095;
        } else {
            values[i] = 0;
        }
    }
    setGrayscale(values);
    gpioTrigger(gsclk, 1, 1);
}
