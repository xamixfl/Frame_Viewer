#ifndef ITERATOREXCEPTION_H
#define ITERATOREXCEPTION_H

#include <cstddef>

#include "BaseException.h"

class ExpiredDataError final : public BaseException {
public:
    ExpiredDataError(
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException("Pointer to deallocated memory", file, classname, function) {
    }
};

class IncompatibleIteratorsError final : public BaseException {
public:
    IncompatibleIteratorsError(
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException("Iterators belong to different containers", file, classname, function) {
    }
};

class InvalidIteratorError final : public BaseException {
    static constexpr size_t MSG_SIZE = 128;

    static std::string format_msg(ptrdiff_t i, size_t limit) {
        char message[MSG_SIZE];
        snprintf(message, MSG_SIZE, "Iterator out of range: i=%td limit=%zu", i, limit);
        return std::string(message);
    }

public:
    InvalidIteratorError(
        ptrdiff_t i,
        size_t limit,
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException(format_msg(i, limit).c_str(), file, classname, function) {
    }
};

#endif // ITERATOREXCEPTION_H
