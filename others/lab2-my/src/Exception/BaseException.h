#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <exception>
#include <ctime>
#include <cstdio>
#include <string>

class BaseException : public std::exception {
    static constexpr size_t BUFF_SIZE = 256;
    char message[BUFF_SIZE];


public:
    BaseException(const char* msg, const char* file, const char* classname, const char* function) {
        const auto _time = time(nullptr);

        snprintf(
            message,
            BUFF_SIZE,
            "%s\nTime: %s\nFile: %s\nClass: %s\nMethod: %s",
            msg, ctime(&_time), file, classname, function
        );
    }

    [[nodiscard]] const char* what() const noexcept override {
        return message;
    }

    virtual ~BaseException() = default;
};

#endif // BASEEXCEPTION_H
