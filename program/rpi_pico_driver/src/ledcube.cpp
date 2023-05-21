//
// Created by mike on 3/27/22.
//

#include "ledcube.h"
#include "config.h"

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

LEDCube::~LEDCube() = default;

// Private
/* ****************************************************************************************************************** */


// Public
/* ****************************************************************************************************************** */
