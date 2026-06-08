#include "model.h"


Model::Model(const Model &other)
    : model(other.model->clone())
{}

Model::Model(std::shared_ptr<ModelImpl> impl)
    : model(std::move(impl))
{}

void Model::accept(const std::shared_ptr<BaseVisitor> &visitor)
{
    visitor->visit(*model);
}

std::shared_ptr<Memento> Model::create_snapshot()
{
    return model->create_snapshot();
}

void Model::restore_snapshot(std::shared_ptr<Memento> snapshot)
{
    model->restore_snapshot(snapshot);
}
