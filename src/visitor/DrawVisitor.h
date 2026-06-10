#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include <memory>
#include "visitor/BaseVisitor.h"
#include "../data/Point.h" 
#include "../data/Face.h"  
#include "../data/Edge.h"
#include "../data/Material.h"

class AbstractDrawerFactory;
class Camera;

class DrawVisitor final : public BaseVisitor {
public:
    DrawVisitor(AbstractDrawerFactory& factory, std::shared_ptr<Camera> camera) noexcept;
    ~DrawVisitor() override = default;

    void visit(BaseModelImpl& impl) noexcept override;
    void visit(BaseCameraImpl& impl) noexcept override;
    void visit(BaseLightImpl& impl) noexcept override;

private:
    std::vector<BaseLightImpl*> _lights;

    AbstractDrawerFactory& _factory;
    std::shared_ptr<Camera> _camera;
};

#endif 
