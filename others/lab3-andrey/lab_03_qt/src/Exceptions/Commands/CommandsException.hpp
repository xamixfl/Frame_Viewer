//
// Created by nuelex on 19/05/25.
//

#ifndef COMMANDSEXCEPTION_HPP
#define COMMANDSEXCEPTION_HPP
#include "../BaseException.hpp"

class ErrorCommand_bad_alloc : public BaseException
{
public:
    ErrorCommand_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "COMMAND: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorCommand_invalid_file : public BaseException
{
public:
    ErrorCommand_invalid_file(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "COMMAND: invalid file") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorCommand_invalid_data : public BaseException
{
public:
    ErrorCommand_invalid_data(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "COMMAND: invalid data") noexcept : BaseException(filename, classname, line, time, error_info) {}
};

class ErrorCommand_out_of_range : public BaseException
{
public:
    ErrorCommand_out_of_range(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "COMMAND: out of range") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //COMMANDSEXCEPTION_HPP
