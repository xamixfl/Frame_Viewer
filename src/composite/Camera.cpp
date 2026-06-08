#include "composite/Camera.h"
#include "bridge/BaseCameraImpl.h"
#include "visitor/BaseVisitor.h"
#include "exception/Exceptions.h"

Camera::Camera(std::unique_ptr<BaseCameraImpl> impl) : _impl(std::move(impl)) {
    if (!_impl) {
        throw NullImplementationError("Camera", __FILE__, "Camera", __FUNCTION__);
    }
}

Camera::~Camera() = default;

void Camera::accept(const std::shared_ptr<BaseVisitor>& visitor) {
    visitor->visit(*_impl);
}

std::shared_ptr<Memento> Camera::createSnapshot() {
    return _impl->createSnapshot();
}

void Camera::restoreSnapshot(const std::shared_ptr<Memento>& snapshot) {
    _impl->restoreSnapshot(snapshot);
}
