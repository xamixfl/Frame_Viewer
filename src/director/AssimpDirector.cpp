#include "director/AssimpDirector.h"
#include "builder/AssimpModelBuilder.h"

AssimpDirector::AssimpDirector(std::unique_ptr<AssimpModelBuilder> builder) noexcept 
    : _builder(std::move(builder)) {}

std::shared_ptr<BaseObject> AssimpDirector::construct(const std::string& filename) {
    if (_builder) {
        _builder->setFilename(filename);
        _builder->build();
        return _builder->getResult();
    }
    return nullptr;
}
