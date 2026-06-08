#ifndef TRANSFORMVISITOR_H
#define TRANSFORMVISITOR_H

#include "visitor/BaseVisitor.h"
#include "data/Transform.h"

class TransformVisitor : public BaseVisitor {
public:
    explicit TransformVisitor(const Transform& t) noexcept : _transform(t) {}
    ~TransformVisitor() override = default;

protected:
    Transform _transform;
};

#endif // TRANSFORMVISITOR_H
