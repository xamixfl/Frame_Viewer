#include "director/CarcasCameraDirector.h"
#include "builder/CarcasCameraBuilder.h"
#include "bridge/CarcasCamera.h"
#include "composite/Camera.h"

#include <memory>
#include <string>

CarcasCameraDirector::CarcasCameraDirector(std::unique_ptr<CarcasCameraBuilder> builder) noexcept
    : _builder(std::move(builder)) {}

CarcasCameraDirector::~CarcasCameraDirector() = default;

CarcasCameraDirector::ObjectPtr CarcasCameraDirector::construct(const std::string& filename) {
    _builder->setFilename(filename);
    _builder->build();
    auto impl = _builder->getResult();
    return std::make_shared<Camera>(std::move(impl));
}
