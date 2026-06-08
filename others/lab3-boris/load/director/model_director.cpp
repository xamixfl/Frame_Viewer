#include "model_director.h"


ModelDirector::ModelDirector(std::shared_ptr<Builder> _builder)
{
    builder = std::move(_builder);
}

std::shared_ptr<Object> ModelDirector::create()
{
    builder->build();

    return builder->get_result();
}
