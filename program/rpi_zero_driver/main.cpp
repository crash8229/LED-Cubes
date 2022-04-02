#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"
#include <iostream>
#include "TLC5940.h"

int main() {
    TLC5940 led(2, 0, 4, 5, 6);

    char data[5][32] = {{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    for (int num = 0; num < 1000; num++){
        for (char* datum: data) {
            led.setGrayscale(datum);
            TLC5940::sleep({0, 1000000});
        }
    }

//    char cube_on[32] = {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//    led.setRawGrayscale(cube_on);
//    TLC5940::sleep({0, 50000});

    return 0;
}

#pragma clang diagnostic pop