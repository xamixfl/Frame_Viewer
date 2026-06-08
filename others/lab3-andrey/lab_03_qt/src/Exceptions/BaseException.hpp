//
// Created by nuelex on 08/05/25.
//

#ifndef BASEEXCEPTION_HPP
#define BASEEXCEPTION_HPP

#include <stdexcept>
#include <ctime>

class BaseException: public std::exception
{
public:
    BaseException(const char *filename,
            const char *classname,
            const long line,
            const char* time,
            const char* error_info = "Base Error!") noexcept
    {
        sprintf(error_text, "FILE: %s LINE: %ld CLASS: %s TIME: %s\n"
                            "ERROR TEXT: %s",
                        filename, line, classname, time, error_info);
    }

    ~BaseException() override = default;

    [[nodiscard]] const char *what() const noexcept override
    {
        return error_text;
    }

protected:
    static constexpr long error_text_size = 512;
    char error_text[error_text_size] {};
};



#endif //BASEEXCEPTION_HPP
