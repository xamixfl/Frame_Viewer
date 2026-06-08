#ifndef BASECAMERAIMPL_H
#define BASECAMERAIMPL_H

#include <memory>

#include "data/Point.h"

class Memento;

class BaseCameraImpl {
public:
    virtual ~BaseCameraImpl() = default;

    [[nodiscard]] virtual Point getPosition() const noexcept = 0;
    [[nodiscard]] virtual Point getDirection() const noexcept = 0;
    [[nodiscard]] virtual Point getUp() const noexcept = 0;

    virtual void setPosition(const Point& p) noexcept = 0;
    virtual void setDirection(const Point& d) noexcept = 0;
    virtual void setUp(const Point& u) noexcept = 0;

    [[nodiscard]] virtual std::shared_ptr<Memento> createSnapshot() = 0;
    virtual void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) = 0;
};

#endif // BASECAMERAIMPL_H
