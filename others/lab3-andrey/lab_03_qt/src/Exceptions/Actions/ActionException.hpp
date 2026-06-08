//
// Created by nuelex on 18/05/25.
//

#ifndef ACTIONEXCEPTION_HPP
#define ACTIONEXCEPTION_HPP
#include "../BaseException.hpp"

class ErrorAction_invalid_object : public BaseException
{
public:
    ErrorAction_invalid_object(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Action: Invalid object") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorAction_invalid_transform : public BaseException
{
public:
    ErrorAction_invalid_transform(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Action: Invalid transform") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //ACTIONEXCEPTION_HPP
