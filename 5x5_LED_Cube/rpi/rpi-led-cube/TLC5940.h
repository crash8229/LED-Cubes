//
// Created by Mike Umana on 9/20/2021.
//

#ifndef TLC5940_H
#define TLC5940_H


#include <cstdint>

class TLC5940 {
private:
    uint8_t xlat;
    uint8_t blank;
    uint8_t gsclk;
    int spi;

public:
    TLC5940(unsigned spi_ch, uint8_t xlat, uint8_t blank, uint8_t gsclk);
    ~TLC5940();
    void setGrayscale(const uint16_t values[16]) const;
    void setLEDs(uint16_t states) const;
};

#endif //TLC5940_H
