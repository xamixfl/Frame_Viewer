//
// Created by nuelex on 12/05/25.
//

#ifndef MANAGERFACTORYEXCEPTION_HPP
#define MANAGERFACTORYEXCEPTION_HPP
#include "../BaseException.hpp"


class ErrorManagerFactory_bad_alloc : public BaseException
{
public:
    ErrorManagerFactory_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "ManagerFactory: bad alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //MANAGERFACTORYEXCEPTION_HPP
