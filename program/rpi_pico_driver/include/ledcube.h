//
// Created by mike on 3/27/22.
//

#ifndef RPI_PICO_DRIVER_LEDCUBE_H
#define RPI_PICO_DRIVER_LEDCUBE_H

#include "config.h"
#include "tlc5940.h"


class LEDCube {
private:
    TLC5940 tlc;

public:
    LEDCube();

    ~LEDCube();
};


#endif //RPI_PICO_DRIVER_LEDCUBE_H
