#include "director/AssimpDirector.h"
#include "builder/AssimpModelBuilder.h"
#include "reader/AssimpReader.h"

#include <memory>

BaseDirector::ObjectPtr AssimpDirector::construct(const std::string& filename) {
    auto reader = std::make_unique<AssimpReader>();
    auto builder = std::make_unique<AssimpModelBuilder>(std::move(reader));

    builder->setFilename(filename);
    builder->build();
    
    return builder->getResult();
}
