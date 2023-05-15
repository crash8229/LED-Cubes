#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

//
// Created by mike on 3/27/22.
//

#include "ledcube.h"
#include "config.h"
#include "sd_card.h"
#include "ff.h"

LEDCube::LEDCube() {


    /* Init TLC5940 */
    tlc.init(
        TLC_PORT,
        TLC_SCLK,
        TLC_MOSI,
        TLC_XLAT,
        TLC_BLANK,
        TLC_GSCLK,
        TLC_NUM
    );

}

LEDCube::~LEDCube() {

}

// Private
/* ****************************************************************************************************************** */


// Public
/* ****************************************************************************************************************** */


#pragma clang diagnostic pop
