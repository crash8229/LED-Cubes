#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include <iomanip>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/multicore.h"

#include "config.h"
#include "tlc5940.h"
#include "sdcard.h"
#include "ledcube.h"

std::string hexStr(uint8_t *data, uint32_t len)
{
    std::stringstream ss;
    ss << std::hex;

    for( int i(0) ; i < len; ++i )
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}

#ifdef SD_CARD_TEST
void sdCardTest(SDCard card){
    assert(card.isFileOpen());

    const uint numBytes = 209715;
    const uint loopNumReport = 600;
#ifndef SD_CARD_TEST_INF
    const uint numLoop = 2000;
    double resultSeconds = 0;
#endif

    uint8_t buf[numBytes];
    uint bytesRead = 0;
    double sum = 0;
    absolute_time_t startTime;
    absolute_time_t endTime;
    const uint16_t bytesInKB = 1024;
    const uint32_t usecInSec = 1e6;
    uint loopCnt = 0;

    printf("\nReading from %s\n", SD_FILE);
    printf("Performing read speed test\n");
#ifdef SD_CARD_TEST_INF
    printf("Reading %d bytes indefinitely\n\n", numBytes);
#else
    printf("Reading %d bytes %d times\n\n", numBytes, numLoop);
#endif
    printf("Reporting running average of calculated read rate every %d iterations\n", loopNumReport);
#ifdef SD_CARD_TEST_INF
    while (true) {
#else
    while (loopCnt < numLoop) {
#endif
        loopCnt++;
        card.fileSeek(0);
        startTime = get_absolute_time();
        assert(card.fileRead(buf, numBytes, &bytesRead));  // Assert if something happens while reading
        endTime = get_absolute_time();
        sum += (double)absolute_time_diff_us(startTime, endTime)/usecInSec;
        assert(numBytes == bytesRead);  // Assert if the bytes read != bytes requested
        if (loopCnt % loopNumReport == 0) {
            printf("Iteration %6d: Average read rate %8.1f KB/s\n", loopCnt, numBytes/(bytesInKB * sum / loopCnt));
        }
    }

#ifndef SD_CARD_TEST_INF
    resultSeconds = sum/(usecInSec * numLoop);
    printf("\nTook on average %fs to read %06d bytes (total read = %010d bytes)\nFinal average read rate: %8.1f KB/s", resultSeconds, numBytes, numBytes * numLoop, numBytes/(bytesInKB * resultSeconds));
#endif
}
#endif

void core1_main() {
    SDCard card;

#ifdef SD_CARD_TEST
    sdCardTest(card);
    card.closeFile();
    card.unmount();
    return;
#endif
    assert(card.isFileOpen());

    const uint numBytes = 4;
    uint8_t buf[numBytes];
    uint bytesRead = 0;
    card.fileRead(buf, numBytes, &bytesRead);
    printf("Bytes from file: 0x%s\n", hexStr(buf, numBytes).c_str());

    card.closeFile();
    card.unmount();
}

int main() {
#ifdef DEBUG
    sleep_ms(1000);
#endif
    // Start STDIO UART and USB
    stdio_uart_init_full((uart_inst_t *)UART_PORT, UART_BAUD_RATE, UART_TX, UART_RX);
    stdio_usb_init();

    // Start second core
    multicore_launch_core1(core1_main);

    // Turn on all LEDs in the cube
//    uint8_t data[5][32] = {{1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//                                 {1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//                                 {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//                                 {1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//                                 {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    // Make a 3x3 cube inside the 5x5 cube
    uint8_t data[5][32] = {{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                           {1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                           {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                           {1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    TLC5940 tlc(TLC_PORT, TLC_SCLK, TLC_MOSI, TLC_XLAT, TLC_BLANK, TLC_GSCLK, TLC_NUM);
    tlc.ledAllOff();

    const uint msWait = 3;
    while (true) {
        for (uint8_t *datum: data) {
            tlc.setGrayscale(datum);
            sleep_ms(msWait);
        }
    }

}

#pragma clang diagnostic pop
