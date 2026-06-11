#ifndef CameraImpl_H
#define CameraImpl_H

#include <memory>

#include "bridge/BaseCameraImpl.h"
#include "data/Point.h"

class Memento;

class CameraImpl final : public BaseCameraImpl {
public:
    CameraImpl() noexcept = default;
    CameraImpl(const Point& pos, const Point& dir, const Point& u) noexcept
        : _position(pos), _direction(dir), _up(u) {}
    ~CameraImpl() override = default;

    [[nodiscard]] Point getPosition() const noexcept override { return _position; }
    [[nodiscard]] Point getDirection() const noexcept override { return _direction; }
    [[nodiscard]] Point getUp() const noexcept override { return _up; }

    void setPosition(const Point& p) noexcept override { _position = p; }
    void setDirection(const Point& d) noexcept override { _direction = d; }
    void setUp(const Point& u) noexcept override { _up = u; }

    [[nodiscard]] std::shared_ptr<Memento> createSnapshot() override;
    void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) override;

private:
    Point _position;
    Point _direction;
    Point _up;
};

#endif 
