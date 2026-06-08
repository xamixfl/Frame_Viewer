#ifndef CAMERA_H__
#define CAMERA_H__

#include "object.h"
#include "point.h"


class Camera : public UndrawableObject
{
public:
    Camera();
    Camera(Camera &&other) noexcept;
    Camera(Point pos, Point tar, Point up) noexcept;
    explicit Camera(const Camera &other);
    explicit Camera(const CameraImpl &impl);

    void accept(const std::shared_ptr<BaseVisitor> &visitor) override;

    std::shared_ptr<Memento> create_snapshot() override;
    void restore_snapshot(std::shared_ptr<Memento> snapshot) override;

    Point get_position();
    Point get_target();
    Point get_up();

private:
    std::shared_ptr<CameraImpl> camera;
};


class CameraImpl
{
public:
    CameraImpl() = default;
    CameraImpl(CameraImpl &&other) noexcept;
    CameraImpl(Point pos, Point tar, Point up) noexcept;
    explicit CameraImpl(const CameraImpl &other);

    Point get_position();
    Point get_target();
    Point get_up();

    void set_position(const Point &point);
    void set_target(const Point &point);
    void set_up(const Point &point);

    std::shared_ptr<Memento> create_snapshot();
    void restore_snapshot(std::shared_ptr<Memento> snapshot);

private:
    Point position;
    Point target;
    Point _up;
};

#endif
