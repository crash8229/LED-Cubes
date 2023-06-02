//
// Created by mike on 5/30/23.
//

#include "parserbase.h"

namespace parser {
    // #### Private ####

    // #### Public ####
    // Constructor & Destructor

    // Functions
    SDCard *ParserBase::card() {
        return _card;
    }
    uint ParserBase::size() const {
        return _size;
    }
    uint ParserBase::offset() const {
        return _offset;
    }
    uint ParserBase::payloadOffset() const {
        return _payloadOffset;
    }
    uint ParserBase::payloadCount() const {
        return _payloadCount;
    }

} // parser
