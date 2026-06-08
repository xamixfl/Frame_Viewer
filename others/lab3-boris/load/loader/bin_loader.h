#ifndef BIN_LOADER_H__
#define BIN_LOADER_H__

#include <string>
#include <memory>
#include <cstddef>

#include "loader.h"


class BinLoader : public Loader
{
public:
    BinLoader() = default;
    explicit BinLoader(std::string _filename);
    ~BinLoader() = default;

    void open() override;
    void close() override;
    double read() override;

    bool is_open() override;

private:
    std::string filename;
    FILE *file = nullptr;
};

#endif
