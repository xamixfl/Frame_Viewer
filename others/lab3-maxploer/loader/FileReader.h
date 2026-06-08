#ifndef FILEREADER_H
#define FILEREADER_H

#include <memory>
#include <fstream>
#include "AbstractReader.h"

class FileReader : public AbstractReader
{
public:
    FileReader();
    explicit FileReader(const std::string& filename);
    ~FileReader() = default;

    void open() override;
    void close() override;
    double read() override;

    bool is_open() override;

private:
    std::string filename;
    FILE *file = nullptr;
};

#endif // FILEREADER_H
