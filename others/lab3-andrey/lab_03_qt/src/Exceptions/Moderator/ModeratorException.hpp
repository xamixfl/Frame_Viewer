//
// Created by nuelex on 25/05/25.
//

#ifndef MODERATOREXCEPTION_HPP
#define MODERATOREXCEPTION_HPP
#include "../BaseException.hpp"

class ErrorModerator_bad_alloc : public BaseException
{
public:
    ErrorModerator_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "MODERATOR: Bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorModerator_invalid_filename : public BaseException
{
public:
    ErrorModerator_invalid_filename(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "MODERATOR: Invalid filename") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //MODERATOREXCEPTION_HPP
