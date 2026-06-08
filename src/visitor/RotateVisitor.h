#ifndef ROTATEVISITOR_H
#define ROTATEVISITOR_H

#include "visitor/TransformVisitor.h"

class RotateVisitor final : public TransformVisitor {
public:
    using TransformVisitor::TransformVisitor;
    ~RotateVisitor() override = default;

    void visit(BaseModelImpl& impl) noexcept override;
    void visit(BaseCameraImpl& impl) noexcept override;
    void visit(BaseLightImpl& impl) noexcept override;
};

#endif // ROTATEVISITOR_H
