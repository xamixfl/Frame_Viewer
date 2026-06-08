#include "director/SceneDirector.h"
#include "builder/SceneBuilder.h"
#include "bridge/VectorCompositeImpl.h"
#include "composite/CompositeObject.h"

#include <memory>
#include <string>

SceneDirector::SceneDirector(std::unique_ptr<SceneBuilder> builder) noexcept : _builder(std::move(builder)) {}

SceneDirector::~SceneDirector() = default;

SceneDirector::ObjectPtr SceneDirector::construct(const std::string& filename) {
    if (!filename.empty()) {
        _builder->setFilename(filename);
    }
    _builder->build();
    auto impl = _builder->getResult();
    return std::make_shared<CompositeObject>(std::move(impl));
}
