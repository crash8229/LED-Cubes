//
// Created by mike on 6/4/23.
//

#include "test.h"

namespace parser {

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
            printf("%sFrame Payload %02d           : %s\n", prefix.c_str(), i, ParserBase::getHexString(buffer, 0, payloadSize).c_str());
        }
        delete[] buffer;
    }

    void printAnimationInfo(Animation *animation, const std::string& prefix) {
        printf("%sAnimation Info             : Size=%05d   Offset=%07d\n", prefix.c_str(), animation->size(), animation->offset());
        printf("%sAnimation Primary Header   : Type=%02d   Version=%02d\n", prefix.c_str(), animation->type(), animation->version());
        printf("%sAnimation SHA256           : %s\n", prefix.c_str(), animation->sha256().c_str());
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

    void printLibraryInfo(Library *library, const std::string& prefix) {
        printf("%sLibrary Info               : Size=%05d   Offset=%07d\n", prefix.c_str(), library->size(), library->offset());
        printf("%sLibrary Primary Header     : Type=%02d   Version=%02d\n", prefix.c_str(), library->type(), library->version());
        printf("%sLibrary SHA256             : %s\n", prefix.c_str(), library->sha256().c_str());
        printf("%sLibrary Secondary Header   : Name           = %s\n", prefix.c_str(), library->name().c_str());
        printf("%s                           : Time           = %llu\n", prefix.c_str(), library->time());
        printf("%s                           : XSize          = %d\n", prefix.c_str(), library->xSize());
        printf("%s                           : YSize          = %d\n", prefix.c_str(), library->ySize());
        printf("%s                           : ZSize          = %d\n", prefix.c_str(), library->zSize());
        printf("%s                           : TLCCount       = %d\n", prefix.c_str(), library->tlcCount());
        printf("%s                           : AnimationCount = %d\n", prefix.c_str(), library->animationCount());
        printf("%s                           : DataLength     = %llu\n", prefix.c_str(), library->dataLength());
        printf("%sLibrary Payload Info       : PayloadOffset=%05d   PayloadCount=%05d\n", prefix.c_str(), library->payloadOffset(), library->payloadCount());

        Animation animation = Animation();
        for (uint i = 0; i < library->payloadCount(); i++) {
            printf("%sLibrary Payload %02d         : PayloadSize=%05d\n", prefix.c_str(), i, library->payloadSize(i));
            library->getPayload(i, &animation);
            printAnimationInfo(&animation, prefix + "                           : ");
        }
    }

    void printFileInfo(File *file, const std::string& prefix) {
        printf("%sFile Info                  : Size=%05d   Offset=%07d\n", prefix.c_str(), file->size(), file->offset());
        printf("%sFile Primary Header        : Type=%02d   Version=%02d\n", prefix.c_str(), file->type(), file->version());
        printf("%sFile Payload Info          : PayloadOffset=%05d   PayloadCount=%05d   PayloadSize=%05d\n", prefix.c_str(), file->payloadOffset(), file->payloadCount(), file->payloadSize(0));

        Library library = Library();
        file->getPayload(&library);
        printf("%sFile Payload %02d            :\n", prefix.c_str(), 0);
        printLibraryInfo(&library, prefix + "                           : ");
    }
} // parsers
