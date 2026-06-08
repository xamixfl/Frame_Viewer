#ifndef MOVEVISITOR_H
#define MOVEVISITOR_H

#include "visitor/TransformVisitor.h"

class MoveVisitor final : public TransformVisitor {
public:
    using TransformVisitor::TransformVisitor;
    ~MoveVisitor() override = default;

    void visit(BaseModelImpl& impl) noexcept override;
    void visit(BaseCameraImpl& impl) noexcept override;
};

#endif // MOVEVISITOR_H
