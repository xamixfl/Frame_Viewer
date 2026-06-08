#ifndef CMRPTUREADER_HPP
#define CMRPTUREADER_HPP
#include <fstream>

#include "../BasePTUReader.hpp"

class CMRPTUReader final : public BasePTUReader
{
public:
    CMRPTUReader() = default;
    explicit CMRPTUReader(const std::string& filename);
    ~CMRPTUReader() override;

    double read() override;

    [[nodiscard]] bool is_open() const noexcept override { return _stream.is_open(); }
    [[nodiscard]] bool eof()     const noexcept override { return _stream.eof(); }

private:
    std::ifstream _stream;
};

#endif //CMRPTUREADER_HPP
