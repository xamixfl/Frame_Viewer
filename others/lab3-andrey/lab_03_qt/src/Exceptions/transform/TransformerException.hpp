//
// Created by nuelex on 21/05/25.
//

#ifndef TRANSFORMEREXCEPTION_HPP
#define TRANSFORMEREXCEPTION_HPP
#include "../BaseException.hpp"

class ErrorTransformer_invalid_camera : public BaseException
{
public:
    ErrorTransformer_invalid_camera(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "TRANSFORMER: invalid camera") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorTransformer_invalid_camera_parameters : public BaseException
{
public:
    ErrorTransformer_invalid_camera_parameters(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "TRANSFORMER: invalid camera parameters") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorTransformer_bad_alloc : public BaseException
{
public:
    ErrorTransformer_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "TRANSFORMER: Bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //TRANSFORMEREXCEPTION_HPP
