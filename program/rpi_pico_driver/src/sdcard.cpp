//
// Created by mike on 5/5/23.
//

#include "sdcard.h"
#include "hw_config.h"

// hw_config.h definitions
/* ****************************************************************************************************************** */
/* ****************************************************************************************************************** */

// SPI config functions
size_t spi_get_num() { return SDCard::getSPIConfigSize(); }
spi_t *spi_get_by_num(size_t num) {
    if (num <= spi_get_num()) {
        return SDCard::getSPIConfig(num);
    }
    return nullptr;
}

// SD cards functions
size_t sd_get_num() { return SDCard::getAllSDCardInfo().size(); }
sd_card_t *sd_get_by_num(size_t num) {
    if (num <= sd_get_num()) {
        return SDCard::getAllSDCardInfo()[num];
    } else {
        return nullptr;
    }
}

/* ****************************************************************************************************************** */
/* ****************************************************************************************************************** */

// sdcard.h definitions
/* ****************************************************************************************************************** */
/* ****************************************************************************************************************** */
SDCard::SDCard() {
    file = {};
    configured = false;
}

SDCard::~SDCard() {
    if (isFileOpen()) {
        closeFile();
    }
    f_unmount(sdCard.pcName);
}

// Private
/* ****************************************************************************************************************** */
std::vector<spi_t> SDCard::spis;
std::vector<sd_card_t *> SDCard::sdCards;

void SDCard::addSDCard() {
    sdCards.push_back(new sd_card_t);
    sdCards.push_back(&sdCard);
    sdDrive = std::to_string(sdCards.size() - 1) + ":";
    sdCard.pcName = sdDrive.c_str();
}
spi_t *SDCard::addSPIConfig(spi_inst_t* port, uint misoGPIO, uint mosiGPIO, uint sckGPIO, uint baudRate, uint dmaIRQNum) {
    // Check if a config already exists using the port and return the address to that if found
    auto iter = spis.begin();
    for (; iter < spis.end(); iter++) {
        if (iter->hw_inst == port) {
            return &*iter;
        }
    }

    // If we got here, then there were no existing config for the port
    spis.push_back({
       .hw_inst = port,
       .miso_gpio = misoGPIO,
       .mosi_gpio = mosiGPIO,
       .sck_gpio = sckGPIO,
       .baud_rate = baudRate,
       .DMA_IRQ_num = dmaIRQNum
    });
    return &spis[spis.size() - 1];
}

// Public
/* ****************************************************************************************************************** */
size_t SDCard::getSPIConfigSize() {
    return spis.size();
}

spi_t *SDCard::getSPIConfig(size_t idx) {
    return &spis[idx];
}

std::vector<sd_card_t*> SDCard::getAllSDCardInfo() {
    return sdCards;
}

bool SDCard::init() {
    return sd_init_driver();
}

bool SDCard::configureForSDIO(uint cmdGPIO, uint d0GPIO, pio_hw_t *sdioPIO, uint dmaIRQNum,
                              bool useCardDetect, uint cardDetectGPIO, uint cardDetectedTrue) {
    if (!configured) {
        configured = true;
        sdCard = {
            .type = SD_IF_SDIO,
            .sdio_if = sd_sdio_t{
                .CMD_gpio = cmdGPIO,
                .D0_gpio = d0GPIO,
                .SDIO_PIO = sdioPIO,
                .DMA_IRQ_num = dmaIRQNum
            },
            .use_card_detect = useCardDetect,
            .card_detect_gpio = cardDetectGPIO,
            .card_detected_true = cardDetectedTrue
        };
        addSDCard();
    }
    return true;
}

bool SDCard::configureForSPI(spi_inst_t* port, uint misoGPIO, uint mosiGPIO, uint sckGPIO, uint baudRate, uint ssGPIO, uint dmaIRQNum, bool useCardDetect, uint cardDetectGPIO, uint cardDetectedTrue) {
    if (!configured) {
        configured = true;
        sdCard = {
            .type = SD_IF_SPI,
            .spi_if = sd_spi_t{
                .spi = addSPIConfig(port, misoGPIO, mosiGPIO, sckGPIO, baudRate,dmaIRQNum),
                .ss_gpio = ssGPIO,
            },
            .use_card_detect = useCardDetect,
            .card_detect_gpio = cardDetectGPIO,
            .card_detected_true = cardDetectedTrue
        };
        addSDCard();
        return true;
    }
    return false;
}

bool SDCard::isMounted() const {
    return sdCard.fatfs.fs_type != 0;
}

bool SDCard::mount() {
    return f_mount(&sdCard.fatfs, sdCard.pcName, 1) == FR_OK;
}

bool SDCard::unmount() const {
    return f_unmount(sdCard.pcName) == FR_OK;
}

bool SDCard::isFileOpen() const {
    return file.obj.fs != nullptr;
}

bool SDCard::openFile(const std::string &path) {
    return f_open(&file, (sdDrive + path).c_str(), FA_READ) == FR_OK;
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

FSIZE_t SDCard::fileSize(){
    return f_size(&file);
}

bool SDCard::fileRead(uint8_t *buf, uint len, UINT *read) {
    return f_read(&file, buf, len, read) == FR_OK;
}

bool SDCard::isCardInserted() {
    return sd_card_detect(&sdCard);
}

/* ****************************************************************************************************************** */
/* ****************************************************************************************************************** */
