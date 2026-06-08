#include "camera.h"


CameraImpl::CameraImpl(CameraImpl &&other) noexcept
    : position(std::move(other.position)), target(std::move(other.target)),
    _up(std::move(other._up))
{}

CameraImpl::CameraImpl(Point pos, Point tar, Point up) noexcept
    : position(std::move(pos)), target(std::move(tar)), _up(std::move(up))
{}

CameraImpl::CameraImpl(const CameraImpl &other)
    : position(other.position), target(other.target), _up(other._up)
{}

Point CameraImpl::get_position()
{
    return position;
}

Point CameraImpl::get_target()
{
    return target;
}

Point CameraImpl::get_up()
{
    return _up;
}

void CameraImpl::set_position(const Point &point)
{
    position = point;
}

void CameraImpl::set_target(const Point &point)
{
    target = point;
}

void CameraImpl::set_up(const Point &point)
{
    _up = point;
}

std::shared_ptr<Memento> CameraImpl::create_snapshot()
{
    return std::shared_ptr<CameraMemento>(new CameraMemento(position, target, _up));
}

void CameraImpl::restore_snapshot(std::shared_ptr<Memento> snapshot)
{
    std::shared_ptr<CameraMemento> memento = std::dynamic_pointer_cast<CameraMemento>(snapshot);

    if (memento)
    {
        position = memento->pos;
        target = memento->tar;
        _up = memento->up;
    }
}


Camera::Camera()
    : camera(std::make_shared<CameraImpl>())
{}

Camera::Camera(Camera &&other) noexcept
    : camera(std::move(other.camera))
{}

Camera::Camera(Point pos, Point tar, Point up) noexcept
    : camera(std::make_shared<CameraImpl>(std::move(pos), std::move(tar), std::move(up)))
{}

Camera::Camera(const Camera &other)
    : camera(std::make_shared<CameraImpl>(*other.camera))
{}

Camera::Camera(const CameraImpl &impl)
    : camera(std::make_shared<CameraImpl>(impl))
{}

void Camera::accept(const std::shared_ptr<BaseVisitor> &visitor)
{
    visitor->visit(*camera);
}

std::shared_ptr<Memento> Camera::create_snapshot()
{
    return camera->create_snapshot();
}

void Camera::restore_snapshot(std::shared_ptr<Memento> snapshot)
{
    camera->restore_snapshot(snapshot);
}

Point Camera::get_position()
{
    return camera->get_position();
}

Point Camera::get_target()
{
    return camera->get_target();
}

Point Camera::get_up()
{
    return camera->get_up();
}
