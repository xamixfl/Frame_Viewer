#ifndef BASEFIGURELPBUILDER_HPP
#define BASEFIGURELPBUILDER_HPP
#include <memory>

#include "../../Readers/LPReaders/BaseLPReader.hpp"

class BaseFigureLPBuilder
{
public:
    explicit BaseFigureLPBuilder(std::shared_ptr<BaseLPReader> reader) noexcept : _reader(std::move(reader)) {}
    virtual ~BaseFigureLPBuilder() = default;

    BaseFigureLPBuilder(const BaseFigureLPBuilder&) = delete;
    BaseFigureLPBuilder& operator=(const BaseFigureLPBuilder&) = delete;

    virtual void build() = 0;

protected:
    std::shared_ptr<BaseLPReader> _reader;
};



#endif //BASEFIGURELPBUILDER_HPP
