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
    FRESULT fr;

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

    /* Mount SD Card */
    // Initialize SD card
    assert(sd_init_driver());

    // Mount drive
    fr = f_mount(&fs, sd_drive, 1);
    assert(fr == FR_OK);

    // Open file to read
    fr = f_open(&file, filename, FA_READ);
    assert(fr == FR_OK);

    sleep_ms(100);

}

LEDCube::~LEDCube() {
    f_close(&file);
    f_unmount(sd_drive);
}

// Private
/* ****************************************************************************************************************** */


// Public
/* ****************************************************************************************************************** */
FRESULT LEDCube::getBytes(uint8_t *buf, uint *read, uint len) {
    return f_read(&file, buf, len, read);
}

#pragma clang diagnostic pop
