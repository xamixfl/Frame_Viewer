//
// Created by nuelex on 14/05/25.
//

#ifndef DIRECTOREXCEPTION_HPP
#define DIRECTOREXCEPTION_HPP
#include "../BaseException.hpp"


class ErrorDirector_bad_alloc : public BaseException
{
public:
    ErrorDirector_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "DIRECTOR: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorDirector_invalid_file : public BaseException
{
public:
    ErrorDirector_invalid_file(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "DIRECTOR: invalid file") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //DIRECTOREXCEPTION_HPP
