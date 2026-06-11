#include "director/CameraDirector.h"
#include "builder/CameraBuilder.h"
#include "reader/AutoReader.h"
#include "composite/Camera.h"

CameraDirector::CameraDirector(std::unique_ptr<BaseBuilder> builder) noexcept 
    : _builder(std::move(builder)) {}

BaseDirector::ObjectPtr CameraDirector::construct(const std::string& filename) {
    auto reader = std::make_unique<AutoReader>();

    auto builder = std::make_unique<CameraBuiler>(std::move(reader));

    builder->setFilename(filename);
    builder->build();

    auto impl = builder->getResult();
    return std::make_shared<Camera>(std::move(impl));
}
