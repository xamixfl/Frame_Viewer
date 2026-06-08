#ifndef BASEREADER_HPP
#define BASEREADER_HPP
#include <string>

class BaseReader
{
public:
    BaseReader() = default;
    explicit BaseReader(const std::string&) {}
    virtual ~BaseReader() = default;

    virtual double read() = 0;

    [[nodiscard]] virtual bool is_open() const noexcept = 0;
    [[nodiscard]] virtual bool eof() const noexcept = 0;
};

#endif //BASEREADER_HPP
