#ifndef BASEPTUREADER_HPP
#define BASEPTUREADER_HPP

#include "../Base/BaseReader.hpp"

class BasePTUReader : public BaseReader
{
public:
    BasePTUReader() = default;
    explicit BasePTUReader(const std::string& filename) : BaseReader(filename) {}
    ~BasePTUReader() override = default;
};

#endif //BASEPTUREADER_HPP
