//
// Created by nuelex on 21/05/25.
//

#ifndef VECEXCEPTION_HPP
#define VECEXCEPTION_HPP
#include "../BaseException.hpp"

class ErrorVec_invalid_vec : public BaseException
{
public:
    ErrorVec_invalid_vec(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "VEC: invalid vec") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //VECEXCEPTION_HPP
