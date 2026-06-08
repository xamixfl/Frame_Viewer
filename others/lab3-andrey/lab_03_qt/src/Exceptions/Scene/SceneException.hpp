//
// Created by nuelex on 11/05/25.
//

#ifndef SCENEEXCEPTION_HPP
#define SCENEEXCEPTION_HPP

#include "../BaseException.hpp"

class ErrorScene_invalid_scene : public BaseException
{
public:
    ErrorScene_invalid_scene(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "SCENE: scene is invalid") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorScene_bad_alloc : public BaseException
{
public:
    ErrorScene_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "SCENE: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorScene_out_of_range : public BaseException
{
public:
    ErrorScene_out_of_range(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "SCENE: out of range") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //SCENEEXCEPTION_HPP
