//
// Created by Mike Umana on 9/20/2021.
//

#ifndef TLC5940_H
#define TLC5940_H


#include <cstdint>
#include <vector>
#include <iostream>

class TLC5940 {
private:
    uint8_t xlat;
    uint8_t blank;
    uint8_t gsclk;
    uint8_t  tlc;
    int spi;
    mutable std::vector<char> gs_out_data;

public:
    TLC5940(uint8_t tlc, unsigned spi_ch, uint8_t xlat, uint8_t blank, uint8_t gsclk);
    ~TLC5940();
    static void sleep(struct timespec sleep_time) ;
    void setRawGrayscale(char* spi_data) const;
    void setGrayscale(const uint16_t* values) const;
    void setGrayscale(const char* values) const;

};

#endif //TLC5940_H
