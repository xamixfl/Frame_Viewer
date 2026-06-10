#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <fstream>
#include <string>

#include "reader/BaseReader.h"

class BinaryReader final : public BaseReader {
public:
    BinaryReader() = default;
    ~BinaryReader() override;

    void open(const std::string& filename) override;
    void close() noexcept override;

    double read() override;

    [[nodiscard]] bool isOpen() const noexcept override;
    [[nodiscard]] bool eof() const noexcept override;

private:
    std::string _filename;
    std::ifstream _stream;
};

#endif 
