#include "composite/Light.h" // Предполагаемый заголовочный файл
#include "bridge/BaseLightImpl.h"
#include "visitor/BaseVisitor.h"
#include "exception/Exceptions.h"

Light::Light(std::unique_ptr<BaseLightImpl> impl) : _impl(std::move(impl)) {
    if (!_impl) {
        throw NullImplementationError("Light", __FILE__, "Light", __FUNCTION__);
    }
}

Light::~Light() = default;

void Light::accept(const std::shared_ptr<BaseVisitor>& visitor) {
    visitor->visit(*_impl);
}

std::shared_ptr<Memento> Light::createSnapshot() {
    return _impl->createSnapshot(); 
}

void Light::restoreSnapshot(const std::shared_ptr<Memento>& snapshot) {
    _impl->restoreSnapshot(snapshot);
}
