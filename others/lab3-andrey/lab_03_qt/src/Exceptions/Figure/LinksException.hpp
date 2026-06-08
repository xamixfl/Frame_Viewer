//
// Created by nuelex on 08/05/25.
//

#ifndef LINKSEXCEPTION_HPP
#define LINKSEXCEPTION_HPP

#include "../BaseException.hpp"

class ErrorLinks_bad_alloc : public BaseException
{
public:
    ErrorLinks_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "lINKS: bad_alloc") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //LINKSEXCEPTION_HPP
