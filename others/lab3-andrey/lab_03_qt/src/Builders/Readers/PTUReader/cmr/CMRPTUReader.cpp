#include "CMRPTUReader.hpp"

#include "../../../../Exceptions/Reader/ReaderException.hpp"

CMRPTUReader::CMRPTUReader(const std::string& filename)
{
    _stream.open(filename, std::ios::in);
    if (!_stream.is_open())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorReader_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

CMRPTUReader::~CMRPTUReader()
{
    if (_stream.is_open())
        _stream.close();
}

double CMRPTUReader::read()
{
    if (!_stream.is_open())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorReader_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    double value{};
    _stream >> value;
    if (_stream.fail() && !_stream.eof())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorReader_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
    return value;
}
