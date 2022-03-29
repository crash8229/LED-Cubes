#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#pragma ide diagnostic ignored "modernize-use-bool-literals"
#pragma ide diagnostic ignored "modernize-deprecated-headers"

#include <cstdio>
#include <sstream>
#include <iomanip>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "config.h"
#include "tlc5940.h"
#include "ledcube.h"

const uint LED = 25;

std::string hexStr(uint8_t *data, uint32_t len)
{
    std::stringstream ss;
    ss << std::hex;

    for( int i(0) ; i < len; ++i )
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}

int main() {
    stdio_init_all();

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    TLC5940 tlc(TLC_PORT, TLC_MISO, TLC_CS, TLC_SCLK, TLC_MOSI, TLC_XLAT, TLC_BLANK, TLC_GSCLK, TLC_NUM);

    // Double Pyramid
    uint8_t data[5][32] = {{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                           {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}};
    printf("\nDriving TLC\n");
    gpio_put(LED, 1);
    for (int i = 0; i < 3;i++) {
        for (uint8_t *datum: data) {
            tlc.setGrayscale(datum);
            sleep_ms(50);
        }
    }
    tlc.ledAllOff();
    gpio_put(LED, 0);

    // SD Card Testing
    LEDCube cube;
    const uint len = 4;
    uint8_t buf[len];
    uint numBytes;
    printf("\nReading from %s\n", SD_FILE);
    cube.getBytes(buf, &numBytes,len);
    printf("Bytes from file: 0x%s\n", hexStr(buf, len).c_str());


    // End infinite loop
    printf("\nProgram End\n");
    while (true) {
        sleep_ms(1000);
    }

}

#pragma clang diagnostic pop
