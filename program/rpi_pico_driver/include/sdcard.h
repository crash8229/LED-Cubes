//
// Created by mike on 5/5/23.
//

#ifndef RPI_PICO_DRIVER_SDCARD_H
#define RPI_PICO_DRIVER_SDCARD_H

#include <vector>
#include <unordered_set>
#include "config.h"
#include "sd_card.h"

class SDCard {
private:
    // Variables
    static std::unordered_set<const TCHAR *> drivesInUse;
    static std::vector<sd_card_t *> sdCards;
    FATFS fs{};
    FIL file{};
    sd_card_t sdCard{};
    const TCHAR *fileName = SD_DEFAULT_FILE;

public:
    // Constructor & Destructor
    SDCard();
    ~SDCard();

    // Functions
    static std::vector<sd_card_t*> getAllSDCardInfo();
    static bool init();
    bool configureSDCard(const TCHAR *driveNum, uint cmd_gpio, uint d0_gpio, pio_hw_t *sdio_pio, uint dma_irq_num, bool use_card_detect, uint card_detect_gpio, uint card_detected_true);
    sd_card_t getSDCardInfo();
    bool mount();
    bool unmount();
    [[nodiscard]] bool isFileOpen() const;
    bool openFile();
    bool closeFile();
    bool fileSeek(FSIZE_t pos);
    FSIZE_t fileTell();
    bool fileRead(uint8_t *buf, uint len, UINT *read);
    bool isCardInserted();
};

#endif //RPI_PICO_DRIVER_SDCARD_H
