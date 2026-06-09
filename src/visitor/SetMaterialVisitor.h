#ifndef SETMATERIALVISITOR_H
#define SETMATERIALVISITOR_H

#include "visitor/BaseVisitor.h"
#include "data/Material.h"
#include "bridge/BaseModelImpl.h"

class SetMaterialVisitor final : public BaseVisitor {
public:
    explicit SetMaterialVisitor(const Material& material) noexcept 
        : _material(material) {}
    
    ~SetMaterialVisitor() override = default;

    void visit(BaseModelImpl& impl) noexcept override {
        impl.setMaterial(_material);
    }
    
    void visit(BaseCameraImpl& /*impl*/) noexcept override {}
    void visit(BaseLightImpl& /*impl*/) noexcept override {}

private:
    Material _material;
};

#endif // SETMATERIALVISITOR_H
