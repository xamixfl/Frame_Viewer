#ifndef LIGHT_H
#define LIGHT_H

#include <memory>
#include "composite/InvisibleObject.h"
#include "bridge/BaseLightImpl.h"
#include "visitor/MoveVisitor.h"
#include "visitor/RotateVisitor.h"
#include "visitor/ScaleVisitor.h"
#include "data/Transform.h"

class BaseVisitor;
class Memento;
class Point;

class Light final : public InvisibleObject {
public:
    explicit Light(std::unique_ptr<BaseLightImpl> impl);
    ~Light() override = default;

    void setPosition(const Point& pos) noexcept { _impl->setPosition(pos); }
    Point getPosition() const noexcept { return _impl->getPosition(); }
    void setIntensity(float i) noexcept { _impl->setIntensity(i); }

    void accept(const std::shared_ptr<BaseVisitor>& visitor) override;

    std::shared_ptr<Memento> createSnapshot() override;
    void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) override;
    
    float getIntensity() const { 
        return _impl->getIntensity();
    }

private:
    std::unique_ptr<BaseLightImpl> _impl;
};

#endif
