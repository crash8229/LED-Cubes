//
// Created by mike on 6/4/23.
//

#include "test.h"

namespace parser {

    void printFrameInfo(Frame *frame, const std::string& prefix) {
        printf("%sFrame Info                 : Size=%05llu   Offset=%07llu\n", prefix.c_str(), frame->size(), frame->offset());
        printf("%sFrame Primary Header       : Type=%02hhu   Version=%02d\n", prefix.c_str(), frame->type(), frame->version());
        printf("%sFrame Secondary Header     : Duration=%05d   DataLength=%05d\n", prefix.c_str(), frame->duration(), frame->dataLength());
        printf("%sFrame Payload Info         : PayloadOffset=%05llu   PayloadCount=%05lu   PayloadSize=%05llu\n", prefix.c_str(), frame->payloadOffset(), frame->payloadCount(), frame->payloadSize());

        Frame::FrameData data = frame->getFrameData();
        for (uint i = 0; i < frame->payloadCount(); i++) {
            printf("%sFrame Payload %02d           : %s\n", prefix.c_str(), i, ParserBase::getHexString(&(data.tlcStates[0]), i * frame->payloadSize(), frame->payloadSize()).c_str());
        }
    }

    void printAnimationInfo(Animation *animation, const std::string& prefix) {
        printf("%sAnimation Info             : Size=%05llu   Offset=%07llu\n", prefix.c_str(), animation->size(), animation->offset());
        printf("%sAnimation Primary Header   : Type=%02hhu   Version=%02d\n", prefix.c_str(), animation->type(), animation->version());
        printf("%sAnimation SHA256           : %s\n", prefix.c_str(), animation->sha256().c_str());
        printf("%sAnimation Secondary Header : Name       = %s\n", prefix.c_str(), animation->name().c_str());
        printf("%s                           : Time       = %llu\n", prefix.c_str(), animation->time());
        printf("%s                           : FrameCount = %d\n", prefix.c_str(), animation->frameCount());
        printf("%s                           : DataLength = %lu\n", prefix.c_str(), animation->dataLength());
        printf("%sAnimation Payload Info     : PayloadOffset=%05llu   PayloadCount=%05lu   PayloadSize=%05llu\n", prefix.c_str(), animation->payloadOffset(), animation->payloadCount(), animation->payloadSize());

        Frame frame;
        for (uint i = 0; i < animation->payloadCount(); i++) {
            frame = animation->getPayload(i);
            printf("%sAnimation Payload %02d       :\n", prefix.c_str(), i);
            printFrameInfo(&frame, prefix + "                           : ");
        }
    }

    void printLibraryInfo(Library *library, const std::string& prefix) {
        printf("%sLibrary Info               : Size=%05llu   Offset=%07llu\n", prefix.c_str(), library->size(), library->offset());
        printf("%sLibrary Primary Header     : Type=%02hhu   Version=%02d\n", prefix.c_str(), library->type(), library->version());
        printf("%sLibrary SHA256             : %s\n", prefix.c_str(), library->sha256().c_str());
        printf("%sLibrary Secondary Header   : Name           = %s\n", prefix.c_str(), library->name().c_str());
        printf("%s                           : Time           = %llu\n", prefix.c_str(), library->time());
        printf("%s                           : XSize          = %d\n", prefix.c_str(), library->xSize());
        printf("%s                           : YSize          = %d\n", prefix.c_str(), library->ySize());
        printf("%s                           : ZSize          = %d\n", prefix.c_str(), library->zSize());
        printf("%s                           : TLCCount       = %d\n", prefix.c_str(), library->tlcCount());
        printf("%s                           : AnimationCount = %d\n", prefix.c_str(), library->animationCount());
        printf("%s                           : DataLength     = %llu\n", prefix.c_str(), library->dataLength());
        printf("%sLibrary Payload Info       : PayloadOffset=%05llu   PayloadCount=%05lu\n", prefix.c_str(), library->payloadOffset(), library->payloadCount());

        Animation animation;
        for (uint i = 0; i < library->payloadCount(); i++) {
            printf("%sLibrary Payload %02d         : PayloadSize=%05llu\n", prefix.c_str(), i, library->payloadSize(i));
            animation = library->getPayload(i);
            printAnimationInfo(&animation, prefix + "                           : ");
        }
    }

    void printFileInfo(File *file, const std::string& prefix) {
        printf("%sFile Info                  : Size=%05llu   Offset=%07llu\n", prefix.c_str(), file->size(), file->offset());
        printf("%sFile Primary Header        : Type=%02hhu   Version=%02d\n", prefix.c_str(), file->type(), file->version());
        printf("%sFile Payload Info          : PayloadOffset=%05llu   PayloadCount=%05lu   PayloadSize=%05llu\n", prefix.c_str(), file->payloadOffset(), file->payloadCount(), file->payloadSize());

        Library library;
        library = file->getPayload();
        printf("%sFile Payload %02d            :\n", prefix.c_str(), 0);
        printLibraryInfo(&library, prefix + "                           : ");
    }
} // parsers
