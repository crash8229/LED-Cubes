//
// Created by mike on 5/5/23.
//

#include "sdcard.h"

SDCard::SDCard() {
    /* Mount SD card and open the file */
    // Initialize SD card
    assert(sd_init_driver());
    assert(mount());
    assert(openFile());

}

SDCard::~SDCard() {
    closeFile();
    f_unmount(sdDrive);
}

// Private
/* ****************************************************************************************************************** */


// Public
/* ****************************************************************************************************************** */
bool SDCard::mount() {
    return f_mount(&fs, sdDrive, 1) == FR_OK;
}

bool SDCard::unmount() {
    return f_unmount(sdDrive) == FR_OK;
}

bool SDCard::isFileOpen() {
    return file.obj.fs != nullptr;
}

bool SDCard::openFile() {
    return f_open(&file, fileName, FA_READ) == FR_OK;
}

bool SDCard::closeFile() {
    return f_close(&file) == FR_OK;
}

bool SDCard::fileSeek(FSIZE_t pos) {
    return f_lseek(&file, pos) == FR_OK;
}

FSIZE_t SDCard::fileTell(){
    return f_tell(&file);
}

bool SDCard::fileRead(uint8_t *buf, uint len, UINT *read) {
    return f_read(&file, buf, len, read) == FR_OK;
}
