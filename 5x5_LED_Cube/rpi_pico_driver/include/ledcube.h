//
// Created by mike on 3/27/22.
//

#ifndef RPI_PICO_DRIVER_LEDCUBE_H
#define RPI_PICO_DRIVER_LEDCUBE_H

#include "config.h"
#include "tlc5940.h"
#include "sd_card.h"
#include "ff.h"

class LEDCube {
private:
    TLC5940 tlc;
    FATFS fs;
    FIL file;
    static constexpr TCHAR sd_drive[] = SD_DRIVE;
    static constexpr TCHAR filename[] = SD_FILE;

public:
    LEDCube();

    ~LEDCube();

    FRESULT getBytes(uint8_t *buf, uint *read, uint len);
};


#endif //RPI_PICO_DRIVER_LEDCUBE_H
