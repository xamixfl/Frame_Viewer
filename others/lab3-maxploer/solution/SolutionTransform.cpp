#include "SolutionTransform.h"

SolutionTransform::SolutionTransform() noexcept {}


SolutionTransform::SolutionTransform(const std::shared_ptr<ModelVisitor> visitor) noexcept
    : visitor(visitor)
{}

void SolutionTransform::transform(std::shared_ptr<AbstractObject>& object) const
{
    object->accept(this->visitor);
}
