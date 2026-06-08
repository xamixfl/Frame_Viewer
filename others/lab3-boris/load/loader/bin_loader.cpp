#include "bin_loader.h"


BinLoader::BinLoader(std::string _filename)
    : filename(std::move(_filename))
{}

bool BinLoader::is_open()
{
    return file != nullptr;
}

void BinLoader::open()
{
    if (is_open())
    {
        return;
    }

    file = std::fopen(filename.c_str(), "rb");

    if (!is_open())
    {
        throw std::runtime_error("File cant be open");
    }
}

void BinLoader::close()
{
    if (!is_open())
    {
        throw std::runtime_error("File was not opened");
    }

    std::fclose(file);
    file = nullptr;
}

double BinLoader::read()
{
    if (!is_open())
    {
        throw std::runtime_error("File not open");
    }

    double val;

    if (std::fread(&val, sizeof(double), 1, file) != 1)
    {
        throw std::runtime_error("File read format error");
    }

    return val;
}
