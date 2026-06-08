#include "composite/CompositeObject.h"
#include "bridge/BaseCompositeImpl.h"
#include "bridge/VectorCompositeImpl.h"
#include "memento/Memento.h"

#include <vector>

CompositeObject::CompositeObject() : _impl(std::make_unique<VectorCompositeImpl>()) {}

CompositeObject::CompositeObject(std::unique_ptr<BaseCompositeImpl> impl) noexcept : _impl(std::move(impl)) {}

CompositeObject::~CompositeObject() = default;

bool CompositeObject::add(const ObjectPtr& obj) {
    return _impl->add(obj);
}

bool CompositeObject::remove(Iterator it) {
    return _impl->remove(it);
}

void CompositeObject::accept(const std::shared_ptr<BaseVisitor>& visitor) {
    for (auto & it : *this) {
        if (it) {
            it->accept(visitor);
        }
    }
}

std::shared_ptr<Memento> CompositeObject::createSnapshot() {
    std::vector<std::shared_ptr<Memento>> states;
    for (auto& child : *this) {
        if (child) {
            states.push_back(child->createSnapshot());
        }
    }
    return std::shared_ptr<CompositeMemento>(new CompositeMemento(std::move(states)));
}

void CompositeObject::restoreSnapshot(const std::shared_ptr<Memento>& snapshot) {
    auto composite = std::dynamic_pointer_cast<CompositeMemento>(snapshot);
    if (!composite) {
        return;
    }
    size_t i = 0;
    for (auto it = begin(); it != end() && i < composite->states.size(); ++it, ++i) {
        if (*it) {
            (*it)->restoreSnapshot(composite->states[i]);
        }
    }
}

CompositeObject::Iterator CompositeObject::begin() {
    return _impl->begin();
}

CompositeObject::Iterator CompositeObject::end() {
    return _impl->end();
}
