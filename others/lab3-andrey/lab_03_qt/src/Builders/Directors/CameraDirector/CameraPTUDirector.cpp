#include "CameraPTUDirector.hpp"

#include "../../../BaseObject/Camera/CameraPTU.hpp"

CameraPTUDirector::CameraPTUDirector(std::shared_ptr<CameraPTUBuilder> builder) noexcept
    : _builder(std::move(builder))
{
}

std::shared_ptr<BaseObject> CameraPTUDirector::create()
{
    _builder->build();
    return std::make_shared<CameraPTU>(_builder->getResult());
}
