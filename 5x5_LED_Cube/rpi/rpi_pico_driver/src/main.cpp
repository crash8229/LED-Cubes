#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#pragma ide diagnostic ignored "modernize-use-bool-literals"
#pragma ide diagnostic ignored "modernize-deprecated-headers"

#include <cstdio>
#include <sstream>
#include <iomanip>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "tlc5940.h"
#include "config.h"
#include "sd_card.h"
#include "ff.h"


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
    sleep_ms(5);
#if DEBUG == 1
    sleep_ms(100);
#endif

    stdio_init_all();
    printf("\n");

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    TLC5940 tlc = TLC5940(TLC_PORT, TLC_MISO, TLC_CS, TLC_SCLK, TLC_MOSI, TLC_XLAT, TLC_BLANK, TLC_GSCLK, TLC_NUM);

    // Double Pyramid
    uint8_t data[5][32] = {{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                           {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}};
    printf("Drive TLC\n");
    for (int i = 0; i < 3;i++) {
        for (uint8_t *datum: data) {
            gpio_put(LED, 0);
            sleep_ms(100);
            gpio_put(LED, 1);
            tlc.setGrayscale(datum);
            sleep_ms(100);
        }
    }
    tlc.ledAllOff();
    gpio_put(LED, 0);

    uint8_t data_buffer[1024];
    uint32_t bytes_read;
    uint8_t data_out[4] = {0xAA, 0xBB, 0xCC, 0xDD};

    // SD Card Testing
    FRESULT fr;
    FATFS fs;
    FIL fil;
    int ret;
    char buf[100];
    char filename[] = "test02.txt";
    const TCHAR sd_drive[] = "0:";

    // Wait for user to press 'enter' to continue
    printf("\r\nSD card test. Press 'enter' to start.\r\n");
    while (true) {
        buf[0] = getchar();
        if ((buf[0] == '\r') || (buf[0] == '\n')) {
            break;
        }
    }

    // Initialize SD card
    if (!sd_init_driver()) {
        printf("ERROR: Could not initialize SD card\r\n");
        while (true);
    }

    // Mount drive
    fr = f_mount(&fs, sd_drive, 1);
    if (fr != FR_OK) {
        printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
        while (true);
    }

    // Open file for writing ()
    fr = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file (%d)\r\n", fr);
        while (true);
    }

    // Write something to file
    ret = f_printf(&fil, "This is another test\r\n");
    if (ret < 0) {
        printf("ERROR: Could not write to file (%d)\r\n", ret);
        f_close(&fil);
        while (true);
    }
    ret = f_printf(&fil, "of writing to an SD card.\r\n");
    if (ret < 0) {
        printf("ERROR: Could not write to file (%d)\r\n", ret);
        f_close(&fil);
        while (true);
    }

    // Close file
    fr = f_close(&fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        while (true);
    }

    // Open file for reading
    fr = f_open(&fil, filename, FA_READ);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file (%d)\r\n", fr);
        while (true);
    }

    // Print every line in file over serial
    printf("Reading from file '%s':\r\n", filename);
    printf("---\r\n");
    while (f_gets(buf, sizeof(buf), &fil)) {
        printf(buf);
    }
    printf("\r\n---\r\n");

    // Close file
    printf("Closing file: '%s'\r\n", filename);
    fr = f_close(&fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        while (true);
    }

    // Unmount drive
    printf("Unmounting SD\r\n");
    f_unmount(sd_drive);


    // End infinite loop
    printf("Program End\n");
    while (true) {
        sleep_ms(1000);
    }

}

#pragma clang diagnostic pop
