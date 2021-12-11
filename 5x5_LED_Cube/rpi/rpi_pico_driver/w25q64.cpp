#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"
#pragma ide diagnostic ignored "modernize-deprecated-headers"
//
// Created by mike on 11/30/21.
//

#include "w25q64.h"
#include <cstdio>
#include "pico/stdlib.h"

W25Q64::W25Q64(const SPIConfig *spi_config) {
    // Init class variables
    cfg = spi_config;
//    spi_data.assign(0, 0);

    // Init SPI
    spi_init(cfg->spi_port, 1000 * 1000 * 30);  // 30MHz
    gpio_set_function(cfg->spi_miso, GPIO_FUNC_SPI);
    gpio_set_function(cfg->spi_cs, GPIO_FUNC_SIO);
    gpio_set_function(cfg->spi_sck, GPIO_FUNC_SPI);
    gpio_set_function(cfg->spi_mosi, GPIO_FUNC_SPI);
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(cfg->spi_cs, GPIO_OUT);
    gpio_put(cfg->spi_cs, 1);
}

W25Q64::~W25Q64() {
    // Cleanup
    spi_deinit(cfg->spi_port);
}

void W25Q64::selectCS(bool state) {
    gpio_put(cfg->spi_cs, not state);
}

size_t W25Q64::sendSPI(uint8_t *data, size_t len) {
    size_t bytes_written;
    selectCS(true);
    bytes_written = spi_write_blocking(cfg->spi_port, data, len);
    selectCS(false);
    return bytes_written;
}

size_t W25Q64::sendSPI(uint8_t *out_data, size_t out_len, uint8_t *in_data, size_t in_len) {
    size_t bytes_read;
    selectCS(true);
    spi_write_blocking(cfg->spi_port, out_data, out_len);
    bytes_read = spi_read_blocking(cfg->spi_port, 0, in_data, in_len);
    selectCS(false);
    return bytes_read;
}

size_t W25Q64::getID(uint8_t *data) {
    uint8_t cmd[] = {0x4B};
    return sendSPI(cmd, 1, data, 12);
}

uint8_t W25Q64::getRawStatusRegister1() {
    uint8_t reg;
    uint8_t cmd[] = {0x05};
    sendSPI(cmd, 1, &reg, 1);
    return reg;
}

StatusReg1 W25Q64::getStatusRegister1() {
    uint8_t val = getRawStatusRegister1();
    StatusReg1 reg = {
        static_cast<uint8_t>(val >> 7),
        static_cast<uint8_t>(val >> 6 & 1),
        static_cast<uint8_t>(val >> 5 & 1),
        static_cast<uint8_t>(val >> 2 & 0b111),
        static_cast<uint8_t>(val >> 1 & 1),
        static_cast<uint8_t>(val & 1),
    };
    return reg;
}

uint8_t W25Q64::getRawStatusRegister2() {
    uint8_t reg;
    uint8_t cmd[] = {0x35};
    sendSPI(cmd, 1, &reg, 1);
    return reg;
}

StatusReg2 W25Q64::getStatusRegister2() {
    uint8_t val = getRawStatusRegister2();
    StatusReg2 reg = {
            static_cast<uint8_t>(val >> 7),
            static_cast<uint8_t>(val >> 6 & 1),
            static_cast<uint8_t>(val >> 3 & 0b111),
            static_cast<uint8_t>(val >> 2 & 1),
            static_cast<uint8_t>(val >> 1 & 1),
            static_cast<uint8_t>(val & 1),
    };
    return reg;
}

void W25Q64::writeEnable(){
    uint8_t cmd[] = {0x06};
    sendSPI(cmd, 1);
}

void W25Q64::writeDisable(){
    uint8_t cmd[] = {0x04};
    sendSPI(cmd, 1);
}

size_t W25Q64::readData(uint32_t address, uint32_t num_bytes,uint8_t *data) {
    uint8_t cmd[] = {0x03, static_cast<uint8_t>(address >> 16 & 0xFF), static_cast<uint8_t>(address >> 8 & 0xFF), static_cast<uint8_t>(address & 0xFF)};
    return sendSPI(cmd, 4, data, num_bytes);
}

size_t W25Q64::writeData(uint32_t address, uint16_t num_bytes, uint8_t *data) {
    uint8_t cmd[] = {0x02, static_cast<uint8_t>(address >> 16 & 0xFF), static_cast<uint8_t>(address >> 8 & 0xFF), static_cast<uint8_t>(address & 0xFF)};
    size_t bytes_written;
    selectCS(true);
    spi_write_blocking(cfg->spi_port, cmd, 4);
    bytes_written = spi_write_blocking(cfg->spi_port, data, num_bytes);
    selectCS(false);
    return bytes_written;
}

void W25Q64::erase4K(uint32_t address) {
    uint8_t cmd[] = {0x20, static_cast<uint8_t>(address >> 16 & 0xFF), static_cast<uint8_t>(address >> 8 & 0xFF), static_cast<uint8_t>(address & 0xFF)};
    sendSPI(cmd, 4);
}

void W25Q64::erase32K(uint32_t address) {
    uint8_t cmd[] = {0x52, static_cast<uint8_t>(address >> 16 & 0xFF), static_cast<uint8_t>(address >> 8 & 0xFF), static_cast<uint8_t>(address & 0xFF)};
    sendSPI(cmd, 4);
}

void W25Q64::erase64K(uint32_t address) {
    uint8_t cmd[] = {0xD8, static_cast<uint8_t>(address >> 16 & 0xFF), static_cast<uint8_t>(address >> 8 & 0xFF), static_cast<uint8_t>(address & 0xFF)};
    sendSPI(cmd, 4);
}

void W25Q64::eraseChip() {
    uint8_t cmd[] = {0xC7};
    sendSPI(cmd, 1);
}

void W25Q64::suspend() {
    uint8_t cmd[] = {0x75};
    sendSPI(cmd, 1);
}

void W25Q64::resume() {
    uint8_t cmd[] = {0x7A};
    sendSPI(cmd, 1);
}

void W25Q64::powerDown() {
    uint8_t cmd[] = {0xB9};
    sendSPI(cmd, 1);
}

void W25Q64::powerDownRelease() {
    uint8_t cmd[] = {0xAB};
    sendSPI(cmd, 1);
}

void W25Q64::resetEnable() {
    uint8_t cmd[] = {0x66};
    sendSPI(cmd, 1);
}

void W25Q64::reset() {
    uint8_t cmd[] = {0x99};
    sendSPI(cmd, 1);
}

#pragma clang diagnostic pop
