//
// Created by nuelex on 22/05/25.
//

#ifndef TABLEEXCEPTION_HPP
#define TABLEEXCEPTION_HPP
#include "../BaseException.hpp"


class ErrorTable_no_table : public BaseException
{
public:
    ErrorTable_no_table(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "TABLE: no table") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorTable_invalid_table : public BaseException
{
public:
    ErrorTable_invalid_table(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "TABLE: invalid table") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorTable_bad_alloc : public BaseException
{
public:
    ErrorTable_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "TABLE: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorTable_invalid_data : public BaseException
{
public:
    ErrorTable_invalid_data(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "TABLE: Invalid data") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //TABLEEXCEPTION_HPP
