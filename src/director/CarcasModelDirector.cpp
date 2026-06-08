#include "director/CarcasModelDirector.h"
#include "builder/CarcasModelBuilder.h"
#include "bridge/BaseModelImpl.h"
#include "composite/Model.h"

#include <memory>
#include <string>

CarcasModelDirector::CarcasModelDirector(std::unique_ptr<CarcasModelBuilder> builder) noexcept
    : _builder(std::move(builder)) {}

CarcasModelDirector::~CarcasModelDirector() = default;

CarcasModelDirector::ObjectPtr CarcasModelDirector::construct(const std::string& filename) {
    _builder->setFilename(filename);
    _builder->build();
    auto impl = _builder->getResult();
    return std::make_shared<Model>(std::move(impl));
}
