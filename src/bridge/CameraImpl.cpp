#include "bridge/CameraImpl.h"

#include "memento/Memento.h"

std::shared_ptr<Memento> CameraImpl::createSnapshot() {
    return std::shared_ptr<CameraMemento>(new CameraMemento(_position, _direction, _up));
}

void CameraImpl::restoreSnapshot(const std::shared_ptr<Memento>& snapshot) {
    auto m = std::dynamic_pointer_cast<CameraMemento>(snapshot);
    if (m) {
        _position  = m->position;
        _direction = m->direction;
        _up        = m->up;
    }
}
