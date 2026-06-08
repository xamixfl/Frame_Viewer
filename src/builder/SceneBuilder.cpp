#include "builder/SceneBuilder.h"
#include "bridge/VectorCompositeImpl.h"

SceneBuilder::SceneBuilder(std::unique_ptr<BaseReader> reader) noexcept : BaseBuilder(std::move(reader)) {}

SceneBuilder::~SceneBuilder() = default;

void SceneBuilder::build() {
    _initImpl();
}

std::unique_ptr<VectorCompositeImpl> SceneBuilder::getResult() noexcept {
    return std::move(_impl);
}

void SceneBuilder::_initImpl() {
    _impl = std::make_unique<VectorCompositeImpl>();
}
