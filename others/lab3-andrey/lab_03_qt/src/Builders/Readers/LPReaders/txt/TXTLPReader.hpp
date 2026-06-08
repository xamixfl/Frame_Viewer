#ifndef TXTLPREADER_HPP
#define TXTLPREADER_HPP
#include <fstream>

#include "../BaseLPReader.hpp"

class TXTLPReader final : public BaseLPReader
{
public:
    TXTLPReader() = default;
    explicit TXTLPReader(const std::string& filename);
    ~TXTLPReader() override;

    double read() override;

    [[nodiscard]] bool is_open() const noexcept override { return _stream.is_open(); }
    [[nodiscard]] bool eof()     const noexcept override { return _stream.eof(); }

private:
    std::ifstream _stream;
};

#endif //TXTLPREADER_HPP
