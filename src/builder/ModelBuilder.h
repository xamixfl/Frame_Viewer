#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include <memory>
#include "builder/BaseBuilder.h"

class Model;

class ModelBuilder final : public BaseBuilder {
public:
    explicit ModelBuilder(std::unique_ptr<BaseReader> reader) noexcept;
    ~ModelBuilder() override;

    void build() override;

    [[nodiscard]] std::unique_ptr<Model> getResult() noexcept;

private:
    std::unique_ptr<Model> _impl;

    void _checkReader() const;
    void _loadData();
    void _assembleResult();
};

#endif // MODELBUILDER_H
