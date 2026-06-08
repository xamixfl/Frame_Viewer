//
// Created by nuelex on 18/05/25.
//

#ifndef BASEOBJECTHASHEXCEPTION_HPP
#define BASEOBJECTHASHEXCEPTION_HPP
#include "../BaseException.hpp"


class ErrorBaseObjectHash_invalid_key : public BaseException
{
public:
    ErrorBaseObjectHash_invalid_key(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "BaseObjectHash: invalid key") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //BASEOBJECTHASHEXCEPTION_HPP
