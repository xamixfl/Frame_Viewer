#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <cstdio>
#include <cstddef>
#include <string>

#include "exception/BaseException.h"

class FileOpenError final : public BaseException {
    static constexpr size_t MSG_SIZE = 256;

    static std::string formatMsg(const char* filename) {
        char buf[MSG_SIZE];
        snprintf(buf, MSG_SIZE, "Couldn't open file: %s", filename ? filename : "");
        return {buf};
    }

public:
    FileOpenError(
        const char* filename,
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException(formatMsg(filename).c_str(), file, classname, function) {}
};

class FileReadError final : public BaseException {
public:
    FileReadError(
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException("Failed to read value from file", file, classname, function) {}
};

class FileNotOpenError final : public BaseException {
public:
    FileNotOpenError(
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException("Operation on closed file stream", file, classname, function) {}
};

class BuilderNotReadyError final : public BaseException {
public:
    BuilderNotReadyError(
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException("Builder has no open reader", file, classname, function) {}
};

class InvalidFileFormatError final : public BaseException {
    static constexpr size_t MSG_SIZE = 256;

    static std::string formatMsg(const char* reason) {
        char buf[MSG_SIZE];
        snprintf(buf, MSG_SIZE, "Invalid file format: %s", reason ? reason : "");
        return {buf};
    }

public:
    InvalidFileFormatError(
        const char* reason,
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException(formatMsg(reason).c_str(), file, classname, function) {}
};

class InvalidSceneError final : public BaseException {
public:
    InvalidSceneError(
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException("Object is not a Scene", file, classname, function) {}
};

class ObjectNotFoundError final : public BaseException {
    static constexpr size_t MSG_SIZE = 128;

    static std::string formatMsg(size_t id) {
        char buf[MSG_SIZE];
        snprintf(buf, MSG_SIZE, "Object with id=%zu not found in scene", id);
        return {buf};
    }

public:
    ObjectNotFoundError(
        size_t id,
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException(formatMsg(id).c_str(), file, classname, function) {}
};

class InvalidCameraError final : public BaseException {
    static constexpr size_t MSG_SIZE = 128;

    static std::string formatMsg(size_t id) {
        char buf[MSG_SIZE];
        snprintf(buf, MSG_SIZE, "Object with id=%zu is not a Camera", id);
        return {buf};
    }

public:
    InvalidCameraError(
        size_t id,
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException(formatMsg(id).c_str(), file, classname, function) {}
};

class NullImplementationError final : public BaseException {
    static constexpr size_t MSG_SIZE = 128;

    static std::string formatMsg(const char* type) {
        char buf[MSG_SIZE];
        snprintf(buf, MSG_SIZE, "Null implementation passed to %s", type ? type : "object");
        return {buf};
    }

public:
    NullImplementationError(
        const char* type,
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException(formatMsg(type).c_str(), file, classname, function) {}
};

class NullObjectError final : public BaseException {
public:
    NullObjectError(
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException("Null object pointer", file, classname, function) {}
};

class UnknownLoadIdError final : public BaseException {
    static constexpr size_t MSG_SIZE = 128;

    static std::string formatMsg(size_t id) {
        char buf[MSG_SIZE];
        snprintf(buf, MSG_SIZE, "No creator factory registered for load id=%zu", id);
        return {buf};
    }

public:
    UnknownLoadIdError(
        size_t id,
        const char* file,
        const char* classname,
        const char* function
    ) noexcept : BaseException(formatMsg(id).c_str(), file, classname, function) {}
};

#endif // EXCEPTIONS_H
