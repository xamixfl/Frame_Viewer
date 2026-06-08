#include "director/AssimpDirector.h"
#include "reader/AssimpReader.h"

AssimpDirector::AssimpDirector(std::unique_ptr<AssimpModelBuilder> builder)
    : _builder(std::move(builder)) 
{
}

std::shared_ptr<BaseObject> AssimpDirector::construct(const std::string& filename) {
    AssimpReader reader; 
    reader.read(filename, *_builder); 
    return _builder->getResult();
}
