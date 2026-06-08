//
// Created by nuelex on 20/05/25.
//

#ifndef DRAWMANAGEREXCEPTION_HPP
#define DRAWMANAGEREXCEPTION_HPP
#include "../BaseException.hpp"

class ErrorDrawManager_invalid_drawer : public BaseException
{
public:
    ErrorDrawManager_invalid_drawer(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Draw Manager: Invalid drawer") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorDrawManager_bad_alloc : public BaseException
{
public:
    ErrorDrawManager_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Draw Manager: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorDrawManager_no_camera : public BaseException
{
public:
    ErrorDrawManager_no_camera(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Draw Manager: no camera") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorDrawManager_invalid_draw : public BaseException
{
public:
    ErrorDrawManager_invalid_draw(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Draw Manager: invalid draw") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorDrawManager_invalid_camera : public BaseException
{
public:
    ErrorDrawManager_invalid_camera(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "Draw Manager: invalid camera") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //DRAWMANAGEREXCEPTION_HPP
