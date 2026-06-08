#ifndef CSVLPREADER_HPP
#define CSVLPREADER_HPP
#include <fstream>

#include "../BaseLPReader.hpp"

class CSVLPReader final : public BaseLPReader
{
public:
    CSVLPReader() = default;
    explicit CSVLPReader(const std::string& filename);
    ~CSVLPReader() override;

    double read() override;

    [[nodiscard]] bool is_open() const noexcept override { return _stream.is_open(); }
    [[nodiscard]] bool eof()     const noexcept override { return _stream.eof(); }

private:
    std::ifstream _stream;
};

#endif //CSVLPREADER_HPP
