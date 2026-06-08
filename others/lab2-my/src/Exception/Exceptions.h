#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "BaseException.h"

class ArgValueError final : public BaseException {
public:
    ArgValueError(
        const char* msg,
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException(msg, file, classname, function) {
    }
};

class MemoryError final : public BaseException {
public:
    MemoryError(
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException("Couldn't allocate memory", file, classname, function) {
    }
};

class IndexError final : public BaseException {
    static constexpr size_t MSG_SIZE = 64;

    static std::string format_msg(size_t i, size_t limit) {
        char message[MSG_SIZE];
        snprintf(message, MSG_SIZE, "Index %zu out of range %zu", i, limit);
        return std::string(message);
    }

public:
    IndexError(
        size_t i,
        size_t limit,
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException(format_msg(i, limit).c_str(), file, classname, function) {
    }
};

class VectorDiffDimsError final : public BaseException {
public:
    VectorDiffDimsError(
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException("Couldn't process operation due to different vectors' dimensions", file, classname, function) {
    }
};

class InvalidDimForCrossProductError final : public BaseException {
public:
    InvalidDimForCrossProductError(
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException("Cross product is available for 3D and 7D only", file, classname, function) {
    }
};

class ZeroVectorSizeError final : public BaseException {
public:
    ZeroVectorSizeError(
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException("Zero-size vector is not allowed", file, classname, function) {
    }
};

class ZeroVectorError final : public BaseException {
public:
    ZeroVectorError(
        const char* file,
        const char* classname,
        const char* function
    ) : BaseException("Couldn't process operation due to zero vector", file, classname, function) {
    }
};

#endif // EXCEPTIONS_H
