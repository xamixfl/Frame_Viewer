#ifndef SCALEVISITOR_H
#define SCALEVISITOR_H

#include "ModelVisitor.h"
#include "../object/carcas/Carcas.h"
#include "../object/camera/Camera.h"
#include "../object/Model.h"

class ScaleVisitor : public ModelVisitor
{
public:
    ScaleVisitor() = default;
    ScaleVisitor(double x, double y, double z);
    ScaleVisitor(const ScaleVisitor& other) = default;
    ScaleVisitor(ScaleVisitor&& other) = default;
    ~ScaleVisitor() = default;

    void visit(Model& obj) override;
    void visit(Camera& obj) override;
    void visit(CompositeObject& obj) override;
};

#endif // SCALEVISITOR_H
