#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include <memory>
#include "builder/BaseBuilder.h"

class VectorCompositeImpl;

class SceneBuilder final : public BaseBuilder {
public:
    explicit SceneBuilder(std::unique_ptr<BaseReader> reader) noexcept;
    ~SceneBuilder() override;

    void build() override;

    [[nodiscard]] std::unique_ptr<VectorCompositeImpl> getResult() noexcept;

private:
    std::unique_ptr<VectorCompositeImpl> _impl;

    void _initImpl();
};

#endif // SCENEBUILDER_H
