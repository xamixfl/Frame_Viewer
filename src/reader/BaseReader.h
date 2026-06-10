#ifndef BASEREADER_H
#define BASEREADER_H

#include <string>

class BaseReader {
public:
    virtual ~BaseReader() = default;

    virtual void open(const std::string& filename) = 0;
    virtual void close() noexcept = 0;

    virtual double read() = 0;

    [[nodiscard]] virtual bool isOpen() const noexcept = 0;
    [[nodiscard]] virtual bool eof() const noexcept = 0;
};

#endif 
