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
//#define SD_RATE 8928571
//#define SD_RATE 10416666
//#define SD_RATE 12500000
//#define SD_RATE 15625000
#define SD_RATE 20833333
//#define SD_RATE 31250000
#define SD_DRIVE "0:"  // Logical Drive Number
//#define SD_FILE "LEDCUBE.bin"
#define SD_FILE "test.bin"

#endif //RPI_PICO_DRIVER_CONFIG_H

// RPi Pico SD Card Read Test Results with the Adafruit SPI/SDIO Breakout Board
//
// SPI:
// 10240 bytes 2000 times:
// | Hz       | Cheap 8GB SD card | PNY 32GB SD Card | SAMSUNG 32GB SD Card |
// | 8928571  | 452.2 KB/s        | 496.7 KB/s       | 518.7 KB/s           |
// | 10416666 | 486.7 KB/s        | 538.4 KB/s       | 564.5 KB/s           |
// | 12500000 | 526.5 KB/s        | 587.7 KB/s       | 618.9 KB/s           |
// | 15625000 | 573.5 KB/s        | 646.8 KB/s       | 684.0 KB/s           |
// | 20833333 | 629.4 KB/s        | 719.3 KB/s       | 766.5 KB/s           |
// | 31250000 | N/A               | N/A              | N/A                  |
//
// 209715 bytes 100 times:
// | Hz       | Cheap 8GB SD card | PNY 32GB SD Card | SAMSUNG 32GB SD Card |
// | 8928571  | 466.0 KB/s        | 505.4 KB/s       | 531.3 KB/s           |
// | 10416666 | 502.6 KB/s        | 548.8 KB/s       | 579.4 KB/s           |
// | 12500000 | 545.0 KB/s        | 599.9 KB/s       | 636.2 KB/s           |
// | 15625000 | 595.5 KB/s        | 661.5 KB/s       | 706.6 KB/s           |
// | 20833333 | 656.1 KB/s        | 737.4 KB/s       | 793.7 KB/s           |
// | 31250000 | N/A               | N/A              | N/A                  |
//
// SDIO:
// 10240 bytes 2000 times:
// | Hz       | Cheap 8GB SD card | PNY 32GB SD Card | SAMSUNG 32GB SD Card |
// | 8928571  |  KB/s        |  KB/s       |  KB/s           |
// | 10416666 |  KB/s        |  KB/s       |  KB/s           |
// | 12500000 |  KB/s        |  KB/s       |  KB/s           |
// | 15625000 |  KB/s        |  KB/s       |  KB/s           |
// | 20833333 |  KB/s        |  KB/s       |  KB/s           |
// | 31250000 | N/A               | N/A              | N/A                  |
//
// 209715 bytes 100 times:
// | Hz       | Cheap 8GB SD card | PNY 32GB SD Card | SAMSUNG 32GB SD Card |
// | 8928571  |  KB/s        |  KB/s       |  KB/s           |
// | 10416666 |  KB/s        |  KB/s       |  KB/s           |
// | 12500000 |  KB/s        |  KB/s       |  KB/s           |
// | 15625000 |  KB/s        |  KB/s       |  KB/s           |
// | 20833333 |  KB/s        |  KB/s       |  KB/s           |
// | 31250000 | N/A               | N/A              | N/A                  |
//