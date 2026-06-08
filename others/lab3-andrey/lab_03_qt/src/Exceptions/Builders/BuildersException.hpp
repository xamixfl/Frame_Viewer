//
// Created by nuelex on 16/05/25.
//

#ifndef BUILDERSEXCEPTION_HPP
#define BUILDERSEXCEPTION_HPP
#include "../BaseException.hpp"


class ErrorBuilder_bad_alloc : public BaseException
{
public:
    ErrorBuilder_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "BUILDER: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorBuilder_invalid_file : public BaseException
{
public:
    ErrorBuilder_invalid_file(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "BUILDER: invalid file") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //BUILDERSEXCEPTION_HPP
