#ifndef CSVPTUREADER_HPP
#define CSVPTUREADER_HPP
#include <fstream>

#include "../BasePTUReader.hpp"

class CSVPTUReader final : public BasePTUReader
{
public:
    CSVPTUReader() = default;
    explicit CSVPTUReader(const std::string& filename);
    ~CSVPTUReader() override;

    double read() override;

    [[nodiscard]] bool is_open() const noexcept override { return _stream.is_open(); }
    [[nodiscard]] bool eof()     const noexcept override { return _stream.eof(); }

private:
    std::ifstream _stream;
};

#endif //CSVPTUREADER_HPP
