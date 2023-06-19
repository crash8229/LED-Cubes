//
// Created by mike on 3/27/22.
//

#ifndef RPI_PICO_DRIVER_LEDCUBE_H
#define RPI_PICO_DRIVER_LEDCUBE_H

#include <pico/util/queue.h>
#include "config.h"
#include "tlc5940.h"
#include "sdcard.h"
#include "parser/file.h"


class LEDCube {
public:
    //Enums
    enum class State {
        STARTED,
        STOPPING,
        STOPPED,
        ERRORED
    };

private:
    // Enums
    enum class Command
    {
        START,
        STOP
    };
    enum class Response {
        OK,
        STOPPED,
        ERROR
    };

    // Structs
    typedef struct {
        uint16_t duration;
        uint16_t dataLength;
        uint8_t *tlcStates;
    } driverPacket;

    // Variables
    TLC5940 *tlc;
    SDCard *card;
    queue_t cmd{};
    queue_t res{};
    queue_t data{};
    std::string _filePath;
    parser::File _file;
    parser::Library _library;
    parser::Animation _animation;
    State currentState = State::STOPPED;
    static LEDCube *cubeToDrive;

    // Function
    void ledDriver();
    void flushDataQueue();
    static void ledDriverCore1();
    driverPacket getFramePacket();

public:
    // Constructor & Destructor
    LEDCube(TLC5940 *tlc, SDCard *card);
    ~LEDCube();

    // Attributes
    std::string filePath();
    parser::File *openedFile();
    parser::Library *openedLibrary();
    parser::Animation *openedAnimation();

    // Functions
    void openFile(const std::string& filePath);
    void closeFile();
    bool isFileOpen();
    void openAnimation(uint8_t index);
    void start();
    void stop();
    // TODO: Add check if animation opened
};

#endif //RPI_PICO_DRIVER_LEDCUBE_H
