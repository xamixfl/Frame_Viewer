#include "camera_director.h"


CameraDirector::CameraDirector(std::shared_ptr<Builder> _builder)
{
    builder = std::move(_builder);
}

std::shared_ptr<Object> CameraDirector::create()
{
    builder->build();

    return builder->get_result();
}
