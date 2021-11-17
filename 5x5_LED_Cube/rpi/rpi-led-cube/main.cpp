#include <iostream>
#include "TLC5940.h"


int main() {
    uint16_t states[16] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
//    TLC5940 led(0, 4, 5, 6, 12);
    TLC5940 led(0, 4, 5, 12);
    struct timespec sleep_time = {0, 30000000};
//    struct timespec sleep_time = {0, 20000000};

    for (int num = 0; num < 10; num++){
        for (uint16_t state: states) {
            led.setLEDs(state);
            while (nanosleep(&sleep_time, &sleep_time));
        }
    }

    return 0;
}
