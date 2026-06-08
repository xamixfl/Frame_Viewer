#ifndef TRANSFORM_VISITOR_H__
#define TRANSFORM_VISITOR_H__

#include "base_visitor.h"
#include "transformer.h"


class TransformVisitor : public BaseVisitor
{
protected:
    Transformer transform;
};


class MoveVisitor : public TransformVisitor
{
public:
    MoveVisitor() = default;
    MoveVisitor(Transformer _transform);
    ~MoveVisitor() = default;

    void visit(ModelImpl &obj) override;
    void visit(CameraImpl &obj) override;
};


class ScaleVisitor : public TransformVisitor
{
public:
    ScaleVisitor() = default;
    ScaleVisitor(Transformer _transform);
    ~ScaleVisitor() = default;

    void visit(ModelImpl &obj) override;
    void visit(CameraImpl &obj) override;
};


class RotateVisitor : public TransformVisitor
{
public:
    RotateVisitor() = default;
    RotateVisitor(Transformer _transform);
    ~RotateVisitor() = default;

    void visit(ModelImpl &obj) override;
    void visit(CameraImpl &obj) override;
};

#endif
