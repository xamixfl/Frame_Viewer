//
// Created by nuelex on 08/05/25.
//

#ifndef POINTSEXCEPTION_HPP
#define POINTSEXCEPTION_HPP

#include "../BaseException.hpp"

class ErrorPoints_bad_alloc : public BaseException
{
public:
    ErrorPoints_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "POINTS: bad_alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //POINTSEXCEPTION_HPP
