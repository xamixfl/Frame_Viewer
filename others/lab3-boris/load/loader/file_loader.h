#ifndef FILE_LOADER_H__
#define FILE_LOADER_H__

#include <string>
#include <memory>
#include <cstddef>

#include "loader.h"


class FileLoader : public Loader
{
public:
    FileLoader() = default;
    explicit FileLoader(std::string _filename);
    ~FileLoader() = default;

    void open() override;
    void close() override;
    double read() override;

    bool is_open() override;

private:
    std::string filename;
    FILE *file = nullptr;
};

#endif
