//
// Created by Mike Umana on 9/20/2021.
//

#include "TLC5940.h"
#include <iostream>
#include <pigpio.h>

TLC5940::TLC5940(unsigned spi_ch, uint8_t xlat, uint8_t blank, uint8_t vprg, uint8_t gsclk) {
    this->xlat = xlat;
    this->blank = blank;
    this->vprg = vprg;
    this->gsclk = gsclk;

    // Init pigpio
    if (gpioInitialise() < 0)
        std::cout << "GPIO did not initialise!" << std::endl;

    // Init GPIO
    gpioSetMode(xlat, PI_OUTPUT);
    gpioSetMode(blank, PI_OUTPUT);
    gpioSetMode(vprg, PI_OUTPUT);
    gpioSetMode(gsclk, PI_OUTPUT);

    gpioWrite(xlat, 0);
    gpioWrite(blank, 0);
    gpioWrite(gsclk, 0);
    gpioWrite(vprg, 0);

    // Init SPI
    spi = spiOpen(spi_ch, 17000000, 0b0000000000000000000000);

    // Set Init Grayscale
    uint16_t gs_values[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    setGrayscale(gs_values);

    // Set DOT correction
//    uint8_t dc_values[16] = {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63};
//    uint8_t dc_values[16] = {10, 10, 10, 10, 10, 10, 10, 10, 63, 63, 63, 63, 63, 63, 63, 0};
//    uint8_t dc_values[16] = {63, 63, 0, 63, 0, 63, 63, 63, 0, 0, 63, 63, 63, 63, 0, 63};
//    uint8_t dc_values[16] = {0, 1 << 4, 1 << 2, 1, 0, 1 << 4, 1 << 2, 1, 0, 1 << 4, 1 << 2, 1, 0, 1 << 4, 1 << 2, 1};  // Make each byte 1
//    setDOTCorrection(dc_values);
//    gpioTrigger(blank, 1, 1);
//    gpioTrigger(gsclk, 1, 1);

    // Start Grayscale clock
//    gpioSetPWMfrequency(gsclk, 500);
//    gpioSetPWMrange(gsclk, 100000);
//    gpioPWM(gsclk, 128);
//    time_sleep(10);
}

TLC5940::~TLC5940() {
    setLEDs(0);

    // Cleanup
    gpioWrite(xlat, 0);
    gpioWrite(blank, 0);
    gpioWrite(gsclk, 0);
    gpioWrite(vprg, 0);

    spiClose(spi);

    gpioTerminate();
}

void TLC5940::setDOTCorrection(const uint8_t *values) const {
    char dot_correction_data[12];
    uint8_t rvalues[16];

    int j;
    for (int i = 15; i >= 0; i--) {
        j = 15 - i;
        rvalues[j] = values[i];
    }

    int dc_idx;
    for (int i = 0; i < 16; i = i + 4) {
        dc_idx = i - i/4;
        dot_correction_data[dc_idx] = rvalues[i] << 2 | (rvalues[i + 1] & 0b110000) >> 4;
        dot_correction_data[dc_idx + 1] = rvalues[i + 1] << 4 | (rvalues[i + 2] & 0b111100) >> 2;
        dot_correction_data[dc_idx + 2] = rvalues[i + 2] << 6 | rvalues[i + 3] & 0b111111;
    }

    // Set DOT correction
    gpioWrite(vprg, 1);
    spiWrite(spi, dot_correction_data, 12);
    gpioTrigger(xlat, 1, 1);
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
    gpioWrite(vprg, 0);
    spiWrite(spi, grayscale_data, 24);
    gpioWrite(blank, 1);
    gpioTrigger(xlat, 1, 1);
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
