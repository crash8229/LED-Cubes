//
// Created by mike on 6/5/23.
//

#ifndef RPI_PICO_DRIVER_TEST_H
#define RPI_PICO_DRIVER_TEST_H

#include <iomanip>
#include "frame.h"
#include "animation.h"
#include "library.h"
#include "file.h"

namespace parser {

    void printFrameInfo(Frame *frame, const std::string& prefix = "") ;
    void printAnimationInfo(Animation *animation, const std::string& prefix = "");
    void printLibraryInfo(Library *library, const std::string& prefix = "");
    void printFileInfo(File *file, const std::string& prefix = "");

} // parser

#endif //RPI_PICO_DRIVER_TEST_H
