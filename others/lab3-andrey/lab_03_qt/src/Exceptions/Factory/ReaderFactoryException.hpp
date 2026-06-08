//
// Created by nuelex on 13/05/25.
//

#ifndef READERFACTORYEXCEPTION_HPP
#define READERFACTORYEXCEPTION_HPP
#include "../BaseException.hpp"


class ErrorReaderFactory_bad_alloc : public BaseException
{
public:
    ErrorReaderFactory_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "ReaderFactory: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorReaderFactory_invalid_file : public BaseException
{
public:
    ErrorReaderFactory_invalid_file(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "ReaderFactory: invalid file") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //READERFACTORYEXCEPTION_HPP
