#ifndef SCALEVISITOR_H
#define SCALEVISITOR_H

#include "visitor/TransformVisitor.h"

class ScaleVisitor final : public TransformVisitor {
public:
    using TransformVisitor::TransformVisitor;
    ~ScaleVisitor() override = default;

    void visit(BaseModelImpl& impl) noexcept override;
    void visit(BaseCameraImpl& impl) noexcept override;
};

#endif // SCALEVISITOR_H
