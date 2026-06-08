//
// Created by nuelex on 02/06/25.
//

#ifndef COMBINEREXCEPTION_HPP
#define COMBINEREXCEPTION_HPP
#include "../BaseException.hpp"

class ErrorCombiner_bad_alloc : public BaseException
{
public:
    ErrorCombiner_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "COMBINER: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //COMBINEREXCEPTION_HPP
