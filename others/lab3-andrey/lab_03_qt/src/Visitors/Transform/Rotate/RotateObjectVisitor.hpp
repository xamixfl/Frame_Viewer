//
// Created by nuelex on 20/05/25.
//

#ifndef ROTATEOBJECTVISITOR_HPP
#define ROTATEOBJECTVISITOR_HPP
#include "../BaseTransformVisitor.hpp"
#include "../../../Transforms/Transforms.hpp"


class RotateObjectVisitor : public BaseTransformVisitor
{
public:
    explicit RotateObjectVisitor(const std::shared_ptr<BaseTransform>& transform);
    ~RotateObjectVisitor() override = default;

    void visit(AbstractFigureLP& figure) override;
    void visit(BaseCameraPTUImpl& camera) override;

private:
    std::shared_ptr<Rotater> _transform;
};



#endif //ROTATEOBJECTVISITOR_HPP
