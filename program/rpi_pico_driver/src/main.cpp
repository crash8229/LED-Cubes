#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/multicore.h"

#include "config.h"
#include "tlc5940.h"
#include "sdcard.h"
#include "ledcube.h"

#ifdef PARSER_TEST
#include "parser/test.h"
#endif


#ifdef SD_CARD_TEST
void sdCardTest(SDCard *card) {
    assert(card->isCardInserted());
    assert(card->isMounted());
    if (card->isFileOpen())
        card->closeFile();

    card->openFile("/test/read.bin");
    assert(card->isFileOpen());

    const uint numBytes = 209715;
//    const uint loopNumReport = 600;
    const uint loopNumReport = 100;
#ifndef SD_CARD_TEST_INF
//    const uint numLoop = 2000;
    const uint numLoop = 500;
#endif

    uint8_t buf[numBytes];
    uint bytesRead = 0;
    double sum = 0;
    absolute_time_t startTime;
    absolute_time_t endTime;
    const uint16_t bytesInKB = 1024;
    const uint32_t usecInSec = 1e6;
    uint loopCnt = 0;
    FSIZE_t maxSeek = card->fileSize() - card->fileSize() % numBytes;

    printf("\nReading from %s\n", card->filePath().c_str());
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
        if (card->fileTell() >= maxSeek) {
            card->fileSeek(0);
        }
        startTime = get_absolute_time();
        assert(card->fileRead(buf, numBytes, &bytesRead));  // Assert if something happens while reading
        endTime = get_absolute_time();
        sum += (double)absolute_time_diff_us(startTime, endTime)/usecInSec;
        assert(numBytes == bytesRead);  // Assert if the bytes read != bytes requested
        if (loopCnt % loopNumReport == 0) {
            printf("Iteration %6d: Average read rate %8.1f KB/s\n", loopCnt, numBytes/(bytesInKB * sum / loopCnt));
        }
    }

#ifndef SD_CARD_TEST_INF
    printf("\nTook on average %fs to read %06d bytes (total read = %010d bytes)\nFinal average read rate: %8.1f KB/s\n", sum / loopCnt, numBytes, numBytes * loopCnt, numBytes/(bytesInKB * sum / loopCnt));
#endif
}
#endif

#ifdef PARSER_TEST
void parserTest(SDCard *card) {
    // #### Test Parsers ####
    assert(card->isCardInserted());
    assert(card->isMounted());
    if (card->isFileOpen())
        card->closeFile();
    printf("\n");

    uint payloadSize;
    uint8_t *buffer;

    // Testing Frame V1 parser
    card->openFile("/test/frame_v1.bin");
    assert(card->isFileOpen());
    printf("Testing Frame parser\n");
    printf("Test file                  : %s\n", card->filePath().c_str());
    parser::Frame frameTest = parser::Frame(card, 0, 2);
    parser::printFrameInfo(&frameTest);
    card->closeFile();
    printf("\n");

    // Testing Animation V1 parser
    card->openFile("/test/animation_v1.bin");
    assert(card->isFileOpen());
    printf("Testing Animation parser\n");
    printf("Test file                  : %s\n", card->filePath().c_str());
    parser::Animation animationTest = parser::Animation(card, 0, 2, 2);
    parser::printAnimationInfo(&animationTest);
    card->closeFile();
    printf("\n");

    // Testing Library V1 parser
    card->openFile("/test/library_v1.bin");
    assert(card->isFileOpen());
    printf("Testing Library parser\n");
    printf("Test file                  : %s\n", card->filePath().c_str());
    parser::Library libraryTest = parser::Library(card, 0);
    parser::printLibraryInfo(&libraryTest);
    card->closeFile();
    printf("\n");

    // Testing File V1 parser
    card->openFile("/test/cube_file_v1.bin");
    assert(card->isFileOpen());
    printf("Testing File parser\n");
    printf("Test file                  : %s\n", card->filePath().c_str());
    parser::File fileTest = parser::File(card, 0);
    parser::printFileInfo(&fileTest);
    card->closeFile();
    printf("\n");
}
#endif

void core1_main() {
    SDCard card;
    card.configureForSDIO(SD_CMD, SD_D0, SD_SDIO_PIO, SD_DMA_IRQ, SD_DET_EN, SD_DET, SD_DET_STATE);
    SDCard::init();
    assert(card.isCardInserted());
    card.mount();
    assert(card.isMounted());
    card.openFile(SD_DEFAULT_FILE);

#ifdef SD_CARD_TEST
    sdCardTest(&card);
    card.closeFile();
    card.unmount();
    assert(!card.isMounted());
    return;
#endif

#ifdef PARSER_TEST
    parserTest(&card);
    card.closeFile();
    card.unmount();
    assert(!card.isMounted());
    return;
#endif

    card.unmount();
    assert(!card.isMounted());
}

// TODO: Add button debouncer
// I just use a timer interrupt to check the buttons every 10-20 ms. Fast enough for good user experience, and slow enough that bouncing contacts are not a problem.

int main() {
#ifdef DEBUG
    sleep_ms(1000);
#endif
    // Start STDIO UART and USB
#ifdef STDIO_UART_ENABLE
    stdio_uart_init_full((uart_inst_t *)UART_PORT, UART_BAUD_RATE, UART_TX, UART_RX);
#endif
#ifdef STDIO_USB_ENABLE
    stdio_usb_init();
#endif
    printf("\n");

    // Start second core
    multicore_launch_core1(core1_main);

    // Turn on all LEDs in the cube
//    uint8_t data[1][32] = {{1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

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

    // Make a 3x3 cube with pillars
//    uint8_t data[5][32] = {{1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
//                           {1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
//                           {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
//                           {1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
//                           {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}};

    TLC5940 tlc(TLC_PORT, TLC_SCLK, TLC_MOSI, TLC_XLAT, TLC_BLANK, TLC_GSCLK, TLC_NUM);
    tlc.ledAllOff();

    const uint waitPerLayer = 3;
    while (true) {
        for (uint8_t *datum: data) {
            tlc.setGrayscale(datum);
            sleep_ms(waitPerLayer);
        }
    }

}

#pragma clang diagnostic pop
