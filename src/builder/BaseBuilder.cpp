#include "builder/BaseBuilder.h"

void BaseBuilder::setFilename(const std::string& filename) const {
    if (_reader) {
        _reader->open(filename);
    }
}
