//
// Created by nuelex on 16/05/25.
//

#ifndef LOADMANAGEREXCEPTION_HPP
#define LOADMANAGEREXCEPTION_HPP

#include "../BaseException.hpp"


class ErrorLoadManager_invalid_file : public BaseException
{
public:
    ErrorLoadManager_invalid_file(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Load Manager: Invalid File") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorLoadManager_bad_alloc : public BaseException
{
public:
    ErrorLoadManager_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Load Manager: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorLoadManager_invalid_loading : public BaseException
{
public:
    ErrorLoadManager_invalid_loading(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Load Manager: invalid loading") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //LOADMANAGEREXCEPTION_HPP
