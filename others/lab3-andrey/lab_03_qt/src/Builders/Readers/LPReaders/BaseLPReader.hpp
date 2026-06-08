#ifndef BASELPREADER_HPP
#define BASELPREADER_HPP

#include "../Base/BaseReader.hpp"

class BaseLPReader : public BaseReader
{
public:
    BaseLPReader() = default;
    explicit BaseLPReader(const std::string& filename) : BaseReader(filename) {}
    ~BaseLPReader() override = default;
};

#endif //BASELPREADER_HPP
