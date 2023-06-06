//
// Created by mike on 6/4/23.
//

#include "test.h"

namespace parser {
    std::string hexStr(uint8_t *data, uint32_t len) {
        std::stringstream ss;
        ss << std::hex;

        for( int i(0) ; i < len; ++i )
            ss << std::setw(2) << std::setfill('0') << (int)data[i];

        return ss.str();
    }

    std::string hexStr(const std::string& data, uint32_t len) {
        return hexStr((uint8_t *)data.c_str(), len);
    }

    void printFrameInfo(Frame *frame, const std::string& prefix) {
        uint payloadSize;
        uint8_t *buffer;

        printf("%sFrame Info                 : Size=%05d   Offset=%07d\n", prefix.c_str(), frame->size(), frame->offset());
        printf("%sFrame Primary Header       : Type=%02d   Version=%02d\n", prefix.c_str(), frame->type(), frame->version());
        printf("%sFrame Secondary Header     : Duration=%05d   DataLength=%05d\n", prefix.c_str(), frame->duration(), frame->dataLength());
        printf("%sFrame Payload Info         : PayloadOffset=%05d   PayloadCount=%05d   PayloadSize=%05d\n", prefix.c_str(), frame->payloadOffset(), frame->payloadCount(), frame->payloadSize(0));

        payloadSize = frame->payloadSize(0);
        buffer = new uint8_t[payloadSize];
        for (uint i = 0; i < frame->payloadCount(); i++) {
            frame->getPayload(i, buffer);
            printf("%sFrame Payload %02d           : %s\n", prefix.c_str(), i, hexStr(buffer, payloadSize).c_str());
        }
        delete[] buffer;
    }

    void printAnimationInfo(Animation *animation, const std::string& prefix) {
        printf("%sAnimation Info             : Size=%05d   Offset=%07d\n", prefix.c_str(), animation->size(), animation->offset());
        printf("%sAnimation Primary Header   : Type=%02d   Version=%02d\n", prefix.c_str(), animation->type(), animation->version());
        printf("%sAnimation SHA256           : %s\n", prefix.c_str(), hexStr(animation->sha256(), 32).c_str());
        printf("%sAnimation Secondary Header : Name       = %s\n", prefix.c_str(), animation->name().c_str());
        printf("%s                           : Time       = %llu\n", prefix.c_str(), animation->time());
        printf("%s                           : FrameCount = %d\n", prefix.c_str(), animation->frameCount());
        printf("%s                           : DataLength = %lu\n", prefix.c_str(), animation->dataLength());
        printf("%sAnimation Payload Info     : PayloadOffset=%05d   PayloadCount=%05d   PayloadSize=%05d\n", prefix.c_str(), animation->payloadOffset(), animation->payloadCount(), animation->payloadSize(0));

        Frame frame = Frame();
        for (uint i = 0; i < animation->payloadCount(); i++) {
            animation->getPayload(i, &frame);
            printf("%sAnimation Payload %02d       :\n", prefix.c_str(), i);
            printFrameInfo(&frame, prefix + "                           : ");
        }
    }
} // parsers
