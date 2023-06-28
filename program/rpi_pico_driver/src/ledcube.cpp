//
// Created by mike on 3/27/22.
//

#include <stdexcept>
#include <cstring>
#include <pico/time.h>
#include <pico/multicore.h>
#include "config.h"
#include "ledcube.h"


// Private
/* ****************************************************************************************************************** */
LEDCube *LEDCube::cubeToDrive = nullptr;
void LEDCube::ledDriver() {
    driverPacket frame;
    Command currentCommand = Command::START;
    Response resp;
    absolute_time_t frameStartTime;
    const uint8_t numLayers = _library.zSize();
    const uint16_t bytesPerLayer = _library.tlcCount() * parser::Frame::bytesPerTLC;

    tlc->ledAllOff();

    // Wait for the first command
    while (queue_is_empty(&cmd)) {
        sleep_ms(100);
    }
    queue_remove_blocking(&data, &frame);
    frameStartTime = get_absolute_time();
    while (true) {
        if (queue_get_level(&cmd) > 0) {
            queue_remove_blocking(&cmd, &currentCommand);
            resp = Response::OK;
            queue_add_blocking(&res, &resp);
        }

        if (currentCommand == Command::START) {
            if (absolute_time_diff_us(frameStartTime, get_absolute_time()) / 1000 >= frame.duration && queue_get_level(&data) > 0) {
                delete[] frame.tlcStates;
                queue_remove_blocking(&data, &frame);
                frameStartTime = get_absolute_time();
            }
            for (uint8_t layer = 0; layer < numLayers; layer++) {
                tlc->setRawGrayscale(&(frame.tlcStates[layer * bytesPerLayer]));
            }
        }
        else if (currentCommand == Command::STOP) {
            resp = Response::STOPPED;
            queue_add_blocking(&res, &resp);
            return;
        }
    }
}
void LEDCube::ledDriverCore1() {
    if (cubeToDrive == nullptr)
        return;
    cubeToDrive->ledDriver();
}
LEDCube::driverPacket LEDCube::getFramePacket() {
    parser::Frame::FrameData frame;
    driverPacket packet;
    if (_animation.payloadCurrentIndex() < _animation.payloadCount())
        frame = _animation.getPayload(_animation.payloadCurrentIndex()).getFrameData();
    else
        frame = _animation.getPayload(0).getFrameData();

    packet.duration = frame.duration;
    packet.dataLength = frame.tlcStates.capacity();
    packet.tlcStates = new uint8_t[packet.dataLength];
    memcpy(packet.tlcStates, &(frame.tlcStates[0]), packet.dataLength);
    return packet;
}

// Public
/* ****************************************************************************************************************** */
// Constructor & Destructor
LEDCube::LEDCube(TLC5940 *tlc, SDCard *card) {
    // Initialize variables
    this->tlc = tlc;
    this->card = card;

    // Make sure the SD card module is at least initialized
    SDCard::init();

    // Initialize the queues
    queue_init(&cmd, sizeof(Command), 1);
    queue_init(&res, sizeof(Response), 1);
    queue_init(&data, sizeof(driverPacket), 5);
}

LEDCube::~LEDCube() {
    queue_free(&cmd);
    queue_free(&res);
    queue_free(&data);
}

// Attributes
std::string LEDCube::filePath() {
    return _filePath;
}

parser::File *LEDCube::openedFile() {
    return &_file;
}

parser::Library *LEDCube::openedLibrary() {
    return &_library;
}

parser::Animation *LEDCube::openedAnimation() {
    return &_animation;
}

// Functions
void LEDCube::openFile(const std::string& filePath) {
    if (currentState == State::STARTED) {
        stop();
    }
    if (!card->isCardInserted())
        throw std::runtime_error("SD card not inserted");
    if (!card->isMounted()) {
        card->mount();
        if (!card->isMounted())
            throw std::runtime_error("SD card could not be mounted");
    }
    if (card->isFileOpen())
        closeFile();
    if (!card->openFile(filePath))
        throw std::runtime_error("Could not open the file");

    _filePath = card->filePath();
    _file = parser::File(card, 0);
    _library = _file.getPayload();
    _animation = parser::Animation();

    if (_library.tlcCount() != TLC_NUM) {
        closeFile();
        char msg[50];
        sprintf(msg, "This library is meant to drive %u TLCs not %u", _library.tlcCount(), TLC_NUM);
        throw std::invalid_argument(msg);
    }
}

void LEDCube::closeFile() {
    if (currentState == State::STARTED) {
        stop();
    }
    card->closeFile();
    _filePath = "";
    _file = parser::File();
    _library = parser::Library();
    _animation = parser::Animation();
}

bool LEDCube::isFileOpen() {
    return card->isFileOpen();
}

void LEDCube::openAnimation(uint8_t index) {
    if (currentState == State::STARTED) {
        stop();
    }
    _animation = _library.getPayload(index);
}

void LEDCube::closeAnimation() {
    if (isAnimationOpen()) {
        if (currentState == State::STARTED) {
            stop();
        }
        _animation = parser::Animation();
    }
}

bool LEDCube::isAnimationOpen() {
    return _animation.version() > 0;
}

void LEDCube::start() {
    driverPacket packet;
    Command val = Command::START;
    Response resp;
    bool queueFull;

    if (currentState != State::STOPPED) {
        stop();
    }

    // Check if animation is open
    if (!isAnimationOpen()) {
        throw std::runtime_error("No animation has been opened");
    }

    // Start driver on Core 1
    // It will wait for the first command before going into the main loop
    cubeToDrive = this;
    multicore_launch_core1(ledDriverCore1);

    // Fill data queue
    while (!queue_is_full(&data)) {
        packet = getFramePacket();
        queue_add_blocking(&data, &packet);
    }

    // Send START command
    queue_add_blocking(&cmd, &val);
    queue_remove_blocking(&res, &resp);
    if (resp != Response::OK) {
        stop();
        throw std::runtime_error("Could not start led driver");
    }
    currentState = State::STARTED;
    while (true) {
        if (currentState == State::STOPPED) {
            break;
        }
        // Read SD card and fill the queue
        queueFull = queue_is_full(&data);
        if (!queueFull) {
            packet = getFramePacket();
            queue_add_blocking(&data, &packet);
        }
    }

    flushDataQueue();
}

void LEDCube::stop() {
    if (currentState == State::STOPPED) {
        return;
    }
    currentState = State::STOPPING;
    Command val = Command::STOP;
    queue_add_blocking(&cmd, &val);
    Response resp = Response::ERROR;
    absolute_time_t startTime = get_absolute_time();
    while (absolute_time_diff_us(startTime, get_absolute_time()) < 1000000) {
        if (queue_get_level(&res) > 0) {
            queue_try_remove(&res, &resp);
            break;
        }
    }
    multicore_reset_core1();
    cubeToDrive = nullptr;
    tlc->ledAllOff();
    currentState = State::STOPPED;
}

void LEDCube::flushDataQueue() {
    queue_free(&data);
    queue_init(&data, sizeof(parser::Frame::FrameData), 5);
}
