//
// Created by nuelex on 12/05/25.
//

#ifndef FACADEEXCEPTION_HPP
#define FACADEEXCEPTION_HPP
#include "../BaseException.hpp"


class ErrorFacade_bad_alloc : public BaseException
{
public:
    ErrorFacade_bad_alloc(const char *filename,
            const char *classname,
            const long line,
            const char *time,
            const char *error_info = "SCENE: scene is invalid") noexcept : BaseException(filename, classname, line, time, error_info) {}
};



#endif //FACADEEXCEPTION_HPP
