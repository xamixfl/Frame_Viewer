#include "CSVLPReader.hpp"

#include <cctype>
#include <sstream>
#include <string>

#include "../../../../Exceptions/Reader/ReaderException.hpp"

CSVLPReader::CSVLPReader(const std::string& filename)
{
    _stream.open(filename, std::ios::in);
    if (!_stream.is_open())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorReader_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

CSVLPReader::~CSVLPReader()
{
    if (_stream.is_open())
        _stream.close();
}

double CSVLPReader::read()
{
    if (!_stream.is_open())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorReader_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    auto isSep = [](int c) { return c == ',' || c == ';' || std::isspace(c); };

    int c = _stream.peek();
    while (c != EOF && isSep(c))
    {
        _stream.get();
        c = _stream.peek();
    }
    if (c == EOF)
    {
        _stream.setstate(std::ios::eofbit);
        return 0.0;
    }

    std::string token;
    while (c != EOF && !isSep(c))
    {
        token.push_back(static_cast<char>(_stream.get()));
        c = _stream.peek();
    }

    try
    {
        return std::stod(token);
    }
    catch (...)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorReader_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}
