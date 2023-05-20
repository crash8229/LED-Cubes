#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-non-const-global-variables"
//
// Created by mike on 3/21/22.
//

#ifndef RPI_PICO_DRIVER_CONFIG_H
#define RPI_PICO_DRIVER_CONFIG_H

#include "hardware//uart.h"
#include "hardware/spi.h"

// Toggles
#define UART_ENABLE
#define DEBUG
#define SD_CARD_TEST
#define SD_CARD_TEST_INF

// #### UART ####
static const uart_inst_t* UART_PORT      = uart0;
const uint                UART_BAUD_RATE = 115200;
const int                 UART_TX        = PICO_DEFAULT_UART_TX_PIN;
const int                 UART_RX        = PICO_DEFAULT_UART_RX_PIN;

//#### TLC5940 ####
static const spi_inst_t* TLC_PORT  = spi0;
const uint8_t            TLC_NUM   = 2;  // Number of ICs chained together
const uint8_t            TLC_XLAT  = 16;
const uint8_t            TLC_BLANK = 17;
const uint8_t            TLC_SCLK  = 18;
const uint8_t            TLC_MOSI  = 19;
const uint8_t            TLC_GSCLK = 20;

//#### SD Card ####
/*
    | GPIO  | Pico Pin | microSD | Function    |
    | ----  | -------- | ------- | ----------- |
    |  09   |    12    | DET     | Card Detect |
    |  10   |    14    | CLK     | SDIO_CLK    |
    |  11   |    15    | CMD     | SDIO_CMD    |
    |  12   |    16    | DAT0    | SDIO_D0     |
    |  13   |    17    | DAT1    | SDIO_D1     |
    |  14   |    19    | DAT2    | SDIO_D2     |
    |  15   |    20    | DAT3    | SDIO_D3     |

Pins CLK_gpio, D1_gpio, D2_gpio, and D3_gpio are at offsets from pin D0_gpio.
The offsets are determined by sd_driver\SDIO\rp2040_sdio.pio.
    CLK_gpio = (D0_gpio + SDIO_CLK_PIN_D0_OFFSET) % 32;
    As of this writing, SDIO_CLK_PIN_D0_OFFSET is 30,
      which is -2 in mod32 arithmetic, so:
    CLK_gpio = D0_gpio -2.
    D1_gpio = D0_gpio + 1;
    D2_gpio = D0_gpio + 2;
    D3_gpio = D0_gpio + 3;
*/
const bool         SD_DET_EN    = true;
const uint8_t      SD_DET_STATE = 1;
const uint8_t      SD_DET       = 9;
const uint8_t      SD_CMD       = 11;
const uint8_t      SD_D0        = 12;
static const char* SD_DRIVE     = "0:"; // Logical Drive Number
#ifdef SD_CARD_TEST
static const char* SD_FILE      = "test.bin";  // Name of binary to use for SD Card test
#else
static const char* SD_FILE      = "LEDCUBE.bin";
#endif

#endif //RPI_PICO_DRIVER_CONFIG_H

// RPi Pico SD Card Read Test Results with the Adafruit SPI/SDIO Breakout Board
// Code used to read the SD Card: https://github.com/carlk3/no-OS-FatFS-SD-SPI-RPi-Pico
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
// Note: Doesn't seem like I can control the clock
// 10240 bytes 40000 times:
// | Cheap 8GB SD card | PNY 32GB SD Card | SAMSUNG 32GB SD Card |
// | 6975.9 KB/s       | 10615.7 KB/s     | 8070.3 KB/s          |
//
// 209715 bytes 2000 times:
// | Cheap 8GB SD card | PNY 32GB SD Card | SAMSUNG 32GB SD Card |
// | 10622.0 KB/s      | 12893.1 KB/s     | 11424.8 KB/s         |
//
#pragma clang diagnostic push
