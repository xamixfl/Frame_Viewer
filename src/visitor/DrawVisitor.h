#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include <memory>
#include "visitor/BaseVisitor.h"

class AbstractDrawerFactory;
class Camera;

class DrawVisitor final : public BaseVisitor {
public:
    DrawVisitor(AbstractDrawerFactory& factory, std::shared_ptr<Camera> camera) noexcept;
    ~DrawVisitor() override = default;

    void visit(BaseModelImpl& impl) noexcept override;
    void visit(BaseCameraImpl& impl) noexcept override;

private:
    AbstractDrawerFactory& _factory;
    std::shared_ptr<Camera> _camera;
};

#endif // DRAWVISITOR_H
