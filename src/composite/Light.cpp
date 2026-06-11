#include "composite/Light.h" 
#include "bridge/BaseLightImpl.h"
#include "visitor/BaseVisitor.h"
#include "exception/Exceptions.h"
#include "memento/Memento.h"

Light::Light(std::unique_ptr<BaseLightImpl> impl) : _impl(std::move(impl)) {
    if (!_impl) {
        throw NullImplementationError("Light", __FILE__, "Light", __FUNCTION__);
    }
}

void Light::accept(const std::shared_ptr<BaseVisitor>& visitor) {
    visitor->visit(*_impl); 
}

std::shared_ptr<Memento> Light::createSnapshot() {
    return std::shared_ptr<Memento>(new LightMemento(_impl->getPosition(), _impl->getIntensity()));
}

void Light::restoreSnapshot(const std::shared_ptr<Memento>& snapshot) {
    auto memento = std::dynamic_pointer_cast<LightMemento>(snapshot);
    if (memento) {
        _impl->setPosition(memento->position);
        _impl->setIntensity(memento->intensity);
    }
}
