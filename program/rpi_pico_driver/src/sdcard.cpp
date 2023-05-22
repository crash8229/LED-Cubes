//
// Created by mike on 5/5/23.
//

#include "sdcard.h"
#include "hw_config.h"

// hw_config.h definitions
/* ****************************************************************************************************************** */
/* ****************************************************************************************************************** */

// Not using SPI, so return 0 and nullptr
size_t spi_get_num() { return 0; }
spi_t *spi_get_by_num(size_t num) { return nullptr; }

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
SDCard::SDCard() = default;

SDCard::~SDCard() {
    if (isFileOpen()) {
        closeFile();
    }
    f_unmount(sdCard.pcName);
}

// Private
/* ****************************************************************************************************************** */
std::unordered_set<const TCHAR *> SDCard::drivesInUse;
std::vector<sd_card_t *> SDCard::sdCards;

// Public
/* ****************************************************************************************************************** */
std::vector<sd_card_t*> SDCard::getAllSDCardInfo() {
    return sdCards;
}

bool SDCard::init() {
    return sd_init_driver();
}

bool SDCard::configureSDCard(const char *driveNum, uint cmd_gpio, uint d0_gpio, pio_hw_t *sdio_pio, uint dma_irq_num,
                             bool use_card_detect, uint card_detect_gpio, uint card_detected_true) {
    static bool configured;
    if (!configured) {
        uint8_t set_size = drivesInUse.size();
        drivesInUse.insert(driveNum);
        assert(set_size + 1 == drivesInUse.size());

        sdCard.pcName = driveNum;
        sdCard.type = SD_IF_SDIO;
        sdCard.sdio_if.CMD_gpio = cmd_gpio;
        sdCard.sdio_if.D0_gpio = d0_gpio;
        sdCard.sdio_if.SDIO_PIO = sdio_pio;
        sdCard.sdio_if.DMA_IRQ_num = dma_irq_num;
        sdCard.use_card_detect = use_card_detect;
        sdCard.card_detect_gpio = card_detect_gpio;
        sdCard.card_detected_true = card_detected_true;

        sdCards.push_back(&sdCard);
    }
    return true;
}

sd_card_t SDCard::getSDCardInfo() {
    return sdCard;
}

bool SDCard::mount() {
    return f_mount(&fs, sdCard.pcName, 1) == FR_OK;
}

bool SDCard::unmount() {
    return f_unmount(sdCard.pcName) == FR_OK;
}

bool SDCard::isFileOpen() const {
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

bool SDCard::isCardInserted() {
    return sd_card_detect(&sdCard);
}

/* ****************************************************************************************************************** */
/* ****************************************************************************************************************** */
