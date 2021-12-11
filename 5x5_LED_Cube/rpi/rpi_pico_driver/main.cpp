#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#pragma ide diagnostic ignored "modernize-use-bool-literals"
#pragma ide diagnostic ignored "modernize-deprecated-headers"

#include <cstdio>
#include <sstream>
#include <iomanip>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "tlc5940.h"
#include "w25q64.h"

#define DEBUG 1

// TLC5940 Defines
#define TLC_PORT spi0
#define TLC_MISO 16
#define TLC_CS   17
#define TLC_SCK  18
#define TLC_MOSI 19
#define TLC_NUM 2  // Number of ICs chained together
#define TLC_XLAT 13
#define TLC_BLANK 14
#define TLV_GSCLK 15

// W25Q64 Defines
#define W25_PORT spi1
#define W25_MISO 8
#define W25_CS   9
#define W25_SCK  10
#define W25_MOSI 11

// I2C Defines
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
//#define I2C_PORT i2c0
//#define I2C_SDA 8
//#define I2C_SCL 9

const uint LED_PIN = 25;

std::string hexStr(uint8_t *data, uint32_t len)
{
    std::stringstream ss;
    ss << std::hex;

    for( int i(0) ; i < len; ++i )
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}

int main() {

#if DEBUG == 1
    sleep_ms(100);
#endif

    stdio_init_all();
    printf("");
    const TLC5940Config tlc_config = {
            TLC_PORT,
            TLC_MISO,
            TLC_CS,
            TLC_SCK,
            TLC_MOSI,
            TLC_NUM,
            TLC_XLAT,
            TLC_BLANK,
            TLV_GSCLK
    };
    TLC5940 tlc = TLC5940(&tlc_config);

    const SPIConfig w25_config = {
            W25_PORT,
            W25_MISO,
            W25_CS,
            W25_SCK,
            W25_MOSI
    };
    W25Q64 w25 = W25Q64(&w25_config);

    // Double Pyramid
    uint8_t data[5][32] = {{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                           {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}};

    // I2C Initialisation. Using it at 400Khz.
//    i2c_init(I2C_PORT, 400*1000);

//    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
//    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
//    gpio_pull_up(I2C_SDA);
//    gpio_pull_up(I2C_SCL);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
//    while (1) {
//        for (uint8_t *datum: data) {
//            gpio_put(LED_PIN, 0);
//            sleep_ms(250);
//            gpio_put(LED_PIN, 1);
//            tlc.setGrayscale(datum);
//            sleep_ms(250);
//        }
//    }

//    gpio_put(LED_PIN, 1);
//    sleep_ms(5000);
//    gpio_put(LED_PIN, 0);


    uint8_t data_buffer[1024] = {0xAA, 0xBB, 0xCC, 0xDD};
    uint32_t bytes_read;

    // Trigger pulse
    gpio_init(2);
    gpio_set_dir(2, GPIO_OUT);
    gpio_put(2, 1);
    gpio_put(2, 0);

    // Write data
    uint8_t data_out[4] = {0xAA, 0xBB, 0xCC, 0xDD};
    w25.writeEnable();
    absolute_time_t start = get_absolute_time();
    w25.writeData(0, 4, data_out);
    uint8_t reg = w25.getRawStatusRegister1();
    while ((reg & 0b11) != 0) {
        reg = w25.getRawStatusRegister1();

    }
    printf("Time to write: %llu us\n", absolute_time_diff_us(start, get_absolute_time()));

    // Read data
    start = get_absolute_time();
    bytes_read = w25.readData(0, 4, data_buffer);
    printf("Time to read: %llu us\n", absolute_time_diff_us(start, get_absolute_time()));
    printf("Bytes read: %s\n", hexStr(data_out, bytes_read).c_str());

    while (1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
        gpio_put(LED_PIN, 0);
        sleep_ms(1000);
    }
}

#pragma clang diagnostic pop
