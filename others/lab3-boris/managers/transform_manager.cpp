#include "transform_manager.h"


TransformManager::TransformManager(std::shared_ptr<TransformVisitor> v) noexcept
    : visitor(std::move(v))
{}

void TransformManager::transform(std::shared_ptr<Object> &obj)
{
    obj->accept(visitor);
}
