#include "composite/Model.h"
#include "bridge/BaseModelImpl.h"
#include "visitor/BaseVisitor.h"
#include "exception/Exceptions.h"

Model::Model(std::unique_ptr<BaseModelImpl> impl) : _impl(std::move(impl)) {
    if (!_impl) {
        throw NullImplementationError("Model", __FILE__, "Model", __FUNCTION__);
    }
}

Model::~Model() = default;

void Model::accept(const std::shared_ptr<BaseVisitor>& visitor) {
    visitor->visit(*_impl);
}

std::shared_ptr<Memento> Model::createSnapshot() {
    return _impl->createSnapshot();
}

void Model::restoreSnapshot(const std::shared_ptr<Memento>& snapshot) {
    _impl->restoreSnapshot(snapshot);
}
