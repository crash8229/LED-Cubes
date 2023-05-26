//
// Created by mike on 5/5/23.
//

#ifndef RPI_PICO_DRIVER_SDCARD_H
#define RPI_PICO_DRIVER_SDCARD_H

#include <vector>
#include <unordered_set>
#include "config.h"
#include "sd_card.h"
#include <string>

class SDCard {
private:
    // Variables
    static std::vector<spi_t> spis;
    static std::vector<sd_card_t *> sdCards;
    FIL file{};
    std::string sdDrive;
    sd_card_t sdCard{};
    bool configured = false;

    // Functions
    void addSDCard();
    static spi_t *addSPIConfig(spi_inst_t* port, uint misoGPIO, uint mosiGPIO, uint sckGPIO, uint baudRate, uint dmaIRQNum);

public:
    // Constructor & Destructor
    SDCard();
    ~SDCard();

    // Functions
    static size_t getSPIConfigSize();
    static spi_t *getSPIConfig(size_t idx);
    static std::vector<sd_card_t*> getAllSDCardInfo();
    static bool init();
    bool configureForSDIO(uint cmdGPIO, uint d0GPIO, pio_hw_t *sdioPIO, uint dmaIRQNum, bool useCardDetect, uint cardDetectGPIO, uint cardDetectedTrue);
    bool configureForSPI(spi_inst_t* port, uint misoGPIO, uint mosiGPIO, uint sckGPIO, uint baudRate, uint ssGPIO, uint dmaIRQNum, bool useCardDetect, uint cardDetectGPIO, uint cardDetectedTrue);
    [[nodiscard]] bool isMounted() const;
    bool mount();
    [[nodiscard]] bool unmount() const;
    [[nodiscard]] bool isFileOpen() const;
    bool openFile(const std::string &path);
    bool closeFile();
    bool fileSeek(FSIZE_t pos);
    FSIZE_t fileTell();
    FSIZE_t fileSize();
    bool fileRead(uint8_t *buf, uint len, UINT *read);
    bool isCardInserted();
};

#endif //RPI_PICO_DRIVER_SDCARD_H
