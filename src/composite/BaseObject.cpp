#include "composite/BaseObject.h"

size_t& BaseObject::nextId() noexcept {
    static size_t counter = 0;
    return counter;
}

BaseObject::BaseObject() noexcept : _id(nextId()++) {}
