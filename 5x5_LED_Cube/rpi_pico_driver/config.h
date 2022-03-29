//
// Created by mike on 3/21/22.
//

#ifndef RPI_PICO_DRIVER_CONFIG_H
#define RPI_PICO_DRIVER_CONFIG_H

// TODO: Figure out how to turn off led when interacting to SD
#define DEBUG 1
//#define NO_PICO_LED
//#define USE_LED 0

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
#define SD_RATE 1000 * 1000  // 1MHz
#define SD_DRIVE "0:"  // Logical Drive Number
#define SD_FILE "LEDCUBE.bin"

#endif //RPI_PICO_DRIVER_CONFIG_H
