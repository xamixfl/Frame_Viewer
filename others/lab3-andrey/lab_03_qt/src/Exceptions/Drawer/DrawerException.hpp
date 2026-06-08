//
// Created by nuelex on 19/05/25.
//

#ifndef DRAWEREXCEPTION_HPP
#define DRAWEREXCEPTION_HPP
#include "../BaseException.hpp"

class ErrorDrawer_bad_alloc : public BaseException
{
public:
    ErrorDrawer_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "DRAWER: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorDrawer_invalid_data : public BaseException
{
public:
    ErrorDrawer_invalid_data(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "DRAWER: Invalid data") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

#endif //DRAWEREXCEPTION_HPP
