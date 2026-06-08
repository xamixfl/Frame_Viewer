#include "Model.h"

Model::Model(const std::shared_ptr<AbstractCarcas>& model) noexcept
    : model(model)
{}

void Model::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    visitor->visit(*this);
}
