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
    static constexpr TCHAR sdDrive[] = SD_DRIVE;
    static constexpr TCHAR fileName[] = SD_FILE;

    bool sdMount();

    static bool sdUnmount();

    bool sdOpenFile();

    bool sdCloseFile();

public:
    LEDCube();

    ~LEDCube();

    bool getBytes(uint8_t *buf, uint *read, uint len);
};


#endif //RPI_PICO_DRIVER_LEDCUBE_H
