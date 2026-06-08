//
// Created by nuelex on 20/05/25.
//

#ifndef VISITOREXCEPTION_HPP
#define VISITOREXCEPTION_HPP
#include "../BaseException.hpp"

class ErrorVisitor_invalid_data: public BaseException
{
public:
    ErrorVisitor_invalid_data(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "VISITOR: Invalid data") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorVisitor_bad_alloc: public BaseException
{
public:
    ErrorVisitor_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "VISITOR: Bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //VISITOREXCEPTION_HPP
