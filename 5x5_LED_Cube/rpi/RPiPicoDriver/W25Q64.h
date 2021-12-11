//
// Created by mike on 11/30/21.
//

#ifndef RPIPICODRIVER_W25Q64_H
#define RPIPICODRIVER_W25Q64_H

#include <vector>
#include "hardware/spi.h"

typedef struct SPIConfig {
    spi_inst_t *spi_port;
    uint spi_miso;
    uint spi_cs;
    uint spi_sck;
    uint spi_mosi;
} SPIConfig;


typedef struct StatusReg1 {
    uint8_t status_register_protect_0: 1;
    uint8_t sector_protect: 1;
    uint8_t top_bottom_protect: 1;
    uint8_t block_protect_bits: 3;
    uint8_t write_enable_latch: 1;
    uint8_t busy: 1;
} StatusReg1;


typedef struct StatusReg2 {
    uint8_t suspend_status: 1;
    uint8_t complement_protect: 1;
    uint8_t security_register_lock_bits: 3;
    uint8_t reserved: 1;
    uint8_t quad_enable: 1;
    uint8_t status_register_protect_1: 1;
} StatusReg2;

class W25Q64 {
private:
    const SPIConfig* cfg;
    mutable std::vector<uint8_t> spi_data;

    void selectCS(bool state);

    size_t sendSPI(uint8_t* data, size_t len);

    size_t sendSPI(uint8_t* in_data, size_t in_len, uint8_t* out_data, size_t out_len);

public:
    explicit W25Q64(const SPIConfig* spi_config);

    ~W25Q64();

    size_t getID(uint8_t *data);

    uint8_t getRawStatusRegister1();

    StatusReg1 getStatusRegister1();

    uint8_t getRawStatusRegister2();

    StatusReg2 getStatusRegister2();

    void writeEnable();

    void writeDisable();

    size_t readData(uint32_t address, uint32_t num_bytes, uint8_t *data);

    size_t writeData(uint32_t address, uint16_t num_bytes, uint8_t *data);

    void erase4K(uint32_t address);

    void erase32K(uint32_t address);

    void erase64K(uint32_t address);

    void eraseChip();

    void suspend();

    void resume();

    void powerDown();

    void powerDownRelease();

    void resetEnable();

    void reset();
};

#endif //RPIPICODRIVER_W25Q64_H
