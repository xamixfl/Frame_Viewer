#include "file_loader.h"


FileLoader::FileLoader(std::string _filename)
    : filename(std::move(_filename))
{}

bool FileLoader::is_open()
{
    return file != nullptr;
}

void FileLoader::open()
{
    if (is_open())
    {
        return;
    }

    file = std::fopen(filename.c_str(), "r");

    if (!is_open())
    {
        throw std::runtime_error("File cant be open");
    }
}

void FileLoader::close()
{
    if (!is_open())
    {
        throw std::runtime_error("File not opened");
    }

    std::fclose(file);
    file = nullptr;
}

double FileLoader::read()
{
    if (!is_open())
    {
        throw std::runtime_error("File not open");
    }

    double val;

    if (std::fscanf(file, "%lf", &val) != 1)
    {
        throw std::runtime_error("Error reading format");
    }

    return val;
}
