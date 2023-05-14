#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#pragma ide diagnostic ignored "modernize-use-bool-literals"
#pragma ide diagnostic ignored "modernize-deprecated-headers"

#include <iomanip>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/multicore.h"

#include "config.h"
#include "tlc5940.h"
#include "ledcube.h"
#include "sdcard.h"

std::string hexStr(uint8_t *data, uint32_t len)
{
    std::stringstream ss;
    ss << std::hex;

    for( int i(0) ; i < len; ++i )
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}

void sdCardTest(SDCard card){
//    const uint numBytes = 10240;
//    const uint numLoop = 2000;
//    const uint loopNumReport = 600;
    const uint numBytes = 209715;
    const uint numLoop = 100;
    const uint loopNumReport = 30;
    uint8_t buf[numBytes];
    UINT bytesRead = 0;
    uint64_t sum = 0;
    absolute_time_t startTime;
    absolute_time_t endTime;
    double resultSeconds = 0;
    const uint triggerGPIO = 4;

    gpio_init(triggerGPIO);
    gpio_set_dir(triggerGPIO, GPIO_OUT);

    printf("\nReading from %s\n", SD_FILE);
    printf("Performing read speed test (Clock=%dHz)\nReading %d bytes %d times\n\n", SD_RATE, numBytes, numLoop);
    printf("Reporting running average of calculated read rate every %d iterations\n", loopNumReport);
    gpio_put(triggerGPIO, 1);
    for (int i = 1; i <= numLoop; i++) {
        card.fileSeek(0);
        startTime = get_absolute_time();
        assert(card.fileRead(buf, numBytes, &bytesRead));
        endTime = get_absolute_time();
        sum += absolute_time_diff_us(startTime, endTime);
        assert(numBytes == bytesRead);
        if (i % loopNumReport == 0) {
            resultSeconds = sum/(1e6 * i);
            printf("Iteration %d: Average read rate %f KB/s\n", i, numBytes/(1024 * resultSeconds));
        }
    }
    gpio_put(triggerGPIO, 0);

//    printf("Bytes from file: 0x%s\n", hexStr(buf, len).c_str());
    resultSeconds = sum/(1e6 * numLoop);
    printf("\nTook on average %fs to read %d bytes\nFinal average read rate: %f KB/s", resultSeconds, numBytes, numBytes/(1024 * resultSeconds));
}

void core1_main(){
    SDCard card;
    sdCardTest(card);
}

int main() {
#ifdef DEBUG
    sleep_ms(1000);
#endif
    stdio_init_all();

    // Start second core
    multicore_launch_core1(core1_main);

    // Loading Bar
    uint8_t data[5][32] = {{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                           {0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                           {0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                           {0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                           {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    // Loading Bar
//    uint8_t data[10][32] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                           {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                           {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
//                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    TLC5940 tlc(TLC_PORT, TLC_MISO, TLC_CS, TLC_SCLK, TLC_MOSI, TLC_XLAT, TLC_BLANK, TLC_GSCLK, TLC_NUM);
    tlc.ledAllOff();

//    const uint msWait = 3;
    const uint msWait = 250;
    // End infinite loop
    const uint infSleepMS = 1000;
    while (true) {
        for (uint8_t *datum: data) {
            tlc.setGrayscale(datum);
            sleep_ms(msWait);
        }
//        sleep_ms(infSleepMS);
    }

}

#pragma clang diagnostic pop
