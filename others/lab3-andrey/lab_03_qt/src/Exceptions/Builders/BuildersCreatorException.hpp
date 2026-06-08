//
// Created by nuelex on 16/05/25.
//

#ifndef BUILDERSCREATOREXCEPTION_HPP
#define BUILDERSCREATOREXCEPTION_HPP
#include "../BaseException.hpp"


class ErrorBuilderCreator_bad_alloc : public BaseException
{
public:
    ErrorBuilderCreator_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "BUILDER CREATOR: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorBuilderCreator_invalid_file : public BaseException
{
public:
    ErrorBuilderCreator_invalid_file(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "BUILDER CREATOR: invalid file") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //BUILDERSCREATOREXCEPTION_HPP
