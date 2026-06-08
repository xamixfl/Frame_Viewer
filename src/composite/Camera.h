#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "composite/InvisibleObject.h"

class BaseCameraImpl;
class BaseVisitor;
class Memento;

class Camera final : public InvisibleObject {
public:
    explicit Camera(std::unique_ptr<BaseCameraImpl> impl);
    ~Camera() override;

    void accept(const std::shared_ptr<BaseVisitor>& visitor) override;

    [[nodiscard]] std::shared_ptr<Memento> createSnapshot() override;
    void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) override;

private:
    std::unique_ptr<BaseCameraImpl> _impl;

    friend class DrawVisitor;
};

#endif // CAMERA_H
