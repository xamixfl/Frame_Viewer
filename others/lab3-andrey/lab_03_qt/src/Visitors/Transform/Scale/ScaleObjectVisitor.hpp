//
// Created by nuelex on 20/05/25.
//

#ifndef SCALEOBJECTVISITOR_HPP
#define SCALEOBJECTVISITOR_HPP
#include "../BaseTransformVisitor.hpp"
#include "../../../Transforms/Transforms.hpp"

class ScaleObjectVisitor : public BaseTransformVisitor
{
public:
    explicit ScaleObjectVisitor(const std::shared_ptr<BaseTransform> &transform);
    ~ScaleObjectVisitor() override = default;

    void visit(AbstractFigureLP& figure) override;
    void visit(BaseCameraPTUImpl& camera) override {}

private:
    std::shared_ptr<Scaler> _transform;
};



#endif //SCALEOBJECTVISITOR_HPP
