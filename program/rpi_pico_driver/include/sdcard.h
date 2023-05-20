#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-non-const-global-variables"
//
// Created by mike on 5/5/23.
//

#ifndef RPI_PICO_DRIVER_SDCARD_H
#define RPI_PICO_DRIVER_SDCARD_H

#include "config.h"
#include "sd_card.h"
#include "ff.h"

class SDCard {
private:
    FATFS fs;
    FIL file;
    static inline const char *sdDrive = SD_DRIVE;
    static inline const char *fileName = SD_FILE;

public:
    SDCard();

    ~SDCard();

    bool mount();

    bool unmount();

    bool isFileOpen();

    bool openFile();

    bool closeFile();

    bool fileSeek(FSIZE_t pos);

    FSIZE_t fileTell();

    bool fileRead(uint8_t *buf, uint len, UINT *read);
};


#endif //RPI_PICO_DRIVER_SDCARD_H

#pragma clang diagnostic pop
