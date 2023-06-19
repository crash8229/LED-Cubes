#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "config.h"
#include "tlc5940.h"
#include "sdcard.h"
#include "ledcube.h"

#include "test.h"

#ifdef PARSER_TEST
#include "test.h"
#endif


#ifdef SD_CARD_TEST
void sdCardTest(SDCard *card) {
    SDCard::init();
    assert(card->isCardInserted());
    card->mount();
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
    card->closeFile();
    card->unmount();
    assert(!card->isMounted());
#endif
}
#endif

#ifdef PARSER_TEST
void parserTest(SDCard *card) {
    // #### Test Parsers ####
    SDCard::init();
    assert(card->isCardInserted());
    card->mount();
    assert(card->isMounted());
    if (card->isFileOpen())
        card->closeFile();

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

    card->closeFile();
    card->unmount();
    assert(!card->isMounted());
}
#endif


queue_t queue;

// TODO: Add button debouncer
// I just use a timer interrupt to check the buttons every 10-20 ms. Fast enough for good user experience, and slow enough that bouncing contacts are not a problem.

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    auto *cube = (LEDCube *) user_data;
    printf("Stopping the cube\n");
    cube->stop();
    printf("Stopped the cube\n");
    return 0;
}

int main() {
    // Start STDIO UART and USB
#ifdef STDIO_UART_ENABLE
    stdio_uart_init_full((uart_inst_t *)UART_PORT, UART_BAUD_RATE, UART_TX, UART_RX);
#endif
#ifdef STDIO_USB_ENABLE
    stdio_usb_init();
#endif
#ifdef DEBUG
    sleep_ms(1000);
    printf("\n");
#endif

    // Initialize SD card
    SDCard card;
    card.configureForSDIO(SD_CMD, SD_D0, SD_SDIO_PIO, SD_DMA_IRQ, SD_DET_EN, SD_DET, SD_DET_STATE);

#ifdef SD_CARD_TEST
    sdCardTest(&card);
    return 0;
#endif

#ifdef PARSER_TEST
    parserTest(&card);
    return 0;
#endif

//    SDCard::init();
//    card.mount();
//    assert(card.isMounted());
//    card.openFile(SD_DEFAULT_FILE);
//    assert(card.isFileOpen());
//    printf("File                       : %s\n", card.filePath().c_str());
//    parser::File fileParser = parser::File(&card, 0);
//    parser::printFileInfo(&fileParser);
//    card.closeFile();
//    printf("\n");
//    return 0;

    // Initialize TLCs
    TLC5940 tlc(TLC_PORT, TLC_SCLK, TLC_MOSI, TLC_XLAT, TLC_BLANK, TLC_GSCLK, TLC_NUM);

    // Initialize LEDCube
    LEDCube cube = LEDCube(&tlc, &card);

    // Alarm
//    alarm_pool_init_default();
//    add_alarm_in_ms(2000, alarm_callback, &cube, false);

    cube.openFile(SD_DEFAULT_FILE);
    printf("Library: %s\n", cube.openedLibrary()->name().c_str());
    cube.openAnimation(0);
    printf("Animation: %s\n", cube.openedAnimation()->name().c_str());
    cube.start();


    while (true) {
        sleep_ms(1000);
    }

}

#pragma clang diagnostic pop
