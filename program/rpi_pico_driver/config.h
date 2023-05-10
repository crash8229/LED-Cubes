//
// Created by mike on 3/21/22.
//

#ifndef RPI_PICO_DRIVER_CONFIG_H
#define RPI_PICO_DRIVER_CONFIG_H

#include "hardware/spi.h"

#define DEBUG

// TLC5940 Defines
#define TLC_PORT spi0
#define TLC_MISO 16
#define TLC_CS   17
#define TLC_SCLK  18
#define TLC_MOSI 19
#define TLC_NUM 2  // Number of ICs chained together
#define TLC_XLAT 13
#define TLC_BLANK 14
#define TLC_GSCLK 15

// SD Defines
#define SD_PORT spi1
#define SD_MISO 8
#define SD_CS   9
#define SD_SCK  10
#define SD_MOSI 11
//#define SD_RATE 1000 * 1000 * 10  // 10MHz: 457.7 KB/s read rate
//#define SD_RATE 1000 * 1000 * 11  // 11MHz: 488.1 KB/s read rate
#define SD_RATE 1000 * 1000 * 12  // 12MHz: 488.1 KB/s read rate
//#define SD_RATE 1000 * 1000 * 13  // 13MHz: 530.0 KB/s read rate
//#define SD_RATE 1000 * 1000 * 14  // 14MHz: 530.0 KB/s read rate
//#define SD_RATE 1000 * 1000 * 15  // 15MHz: 530.0 KB/s read rate
#define SD_DRIVE "0:"  // Logical Drive Number
//#define SD_FILE "LEDCUBE.bin"
#define SD_FILE "test.bin"

#endif //RPI_PICO_DRIVER_CONFIG_H
