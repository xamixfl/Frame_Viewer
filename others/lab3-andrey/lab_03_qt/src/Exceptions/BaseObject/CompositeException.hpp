//
// Created by nuelex on 10/05/25.
//

#ifndef COMPOSITEEXCEPTION_HPP
#define COMPOSITEEXCEPTION_HPP
#include "../BaseException.hpp"


class ErrorCompositeObject_bad_alloc : public BaseException
{
public:
    ErrorCompositeObject_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "COMPOSITE: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorCompositeObject_out_of_range : public BaseException
{
public:
    ErrorCompositeObject_out_of_range(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "COMPOSITE: out of range") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //COMPOSITEEXCEPTION_HPP
