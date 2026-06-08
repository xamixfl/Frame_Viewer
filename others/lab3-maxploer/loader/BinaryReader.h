#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <memory>
#include <fstream>
#include "AbstractReader.h"

class BinaryReader : public AbstractReader
{
public:
    BinaryReader();
    explicit BinaryReader(const std::string& filename);
    ~BinaryReader() = default;

    void open() override;
    void close() override;
    double read() override;

    bool is_open() override;

private:
    std::string filename;
    FILE *file = nullptr;
};

#endif // BINARYREADER_H
