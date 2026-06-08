#ifndef BASECAMERAPTUBUILDER_HPP
#define BASECAMERAPTUBUILDER_HPP
#include <memory>

#include "../../Readers/PTUReader/BasePTUReader.hpp"

class BaseCameraPTUBuilder
{
public:
    explicit BaseCameraPTUBuilder(std::shared_ptr<BasePTUReader> reader) noexcept : _reader(std::move(reader)) {}
    virtual ~BaseCameraPTUBuilder() = default;

    BaseCameraPTUBuilder(const BaseCameraPTUBuilder&) = delete;
    BaseCameraPTUBuilder& operator=(const BaseCameraPTUBuilder&) = delete;

    virtual void build() = 0;

protected:
    std::shared_ptr<BasePTUReader> _reader;
};



#endif //BASECAMERAPTUBUILDER_HPP
