#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

//
// Created by mike on 3/27/22.
//

#include "ledcube.h"
#include "config.h"
#include "sd_card.h"
#include "ff.h"

LEDCube::LEDCube() {


    /* Init TLC5940 */
    tlc.init(
        TLC_PORT,
        TLC_MISO,
        TLC_CS,
        TLC_SCLK,
        TLC_MOSI,
        TLC_XLAT,
        TLC_BLANK,
        TLC_GSCLK,
        TLC_NUM
    );

    /* Mount SD card and open the file */
    // Initialize SD card
    assert(sd_init_driver());
    assert(sdMount());
    assert(sdOpenFile());

}

LEDCube::~LEDCube() {
    f_close(&file);
    f_unmount(sdDrive);
}

// Private
/* ****************************************************************************************************************** */
bool LEDCube::sdMount() {
    return f_mount(&fs, sdDrive, 1) == FR_OK;
}

bool LEDCube::sdUnmount() {
    return f_mount(nullptr, sdDrive, 0) == FR_OK;
}

bool LEDCube::sdOpenFile() {
    return f_open(&file, fileName, FA_READ) == FR_OK;
}

bool LEDCube::sdCloseFile() {
    return f_close(&file) == FR_OK;
}

// Public
/* ****************************************************************************************************************** */
bool LEDCube::getBytes(uint8_t *buf, uint *read, uint len) {
    return f_read(&file, buf, len, read) == FR_OK;
}

#pragma clang diagnostic pop
