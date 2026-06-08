//
// Created by nuelex on 13/05/25.
//

#ifndef ERRORREADERINVALIDFILE_HPP
#define ERRORREADERINVALIDFILE_HPP
#include "../BaseException.hpp"


class ErrorReader_bad_alloc : public BaseException
{
public:
    ErrorReader_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Reader: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorReader_invalid_file : public BaseException
{
public:
    ErrorReader_invalid_file(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Reader: Invalid File") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorReader_invalid_archive : public BaseException
{
public:
    ErrorReader_invalid_archive(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Reader: Invalid archive") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //ERRORREADERINVALIDFILE_HPP
