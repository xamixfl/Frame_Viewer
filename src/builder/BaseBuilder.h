#ifndef BASEBUILDER_H
#define BASEBUILDER_H

#include <memory>
#include <string>

#include "reader/BaseReader.h"

class BaseBuilder {
public:
    explicit BaseBuilder(std::unique_ptr<BaseReader> reader) noexcept : _reader(std::move(reader)) {}
    virtual ~BaseBuilder() = default;

    BaseBuilder(const BaseBuilder&) = delete;
    BaseBuilder& operator=(const BaseBuilder&) = delete;

    void setFilename(const std::string& filename) const;

    virtual void build() = 0;

protected:
    std::unique_ptr<BaseReader> _reader;
};

#endif
