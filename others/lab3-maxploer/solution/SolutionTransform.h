#ifndef SOLUTIONTRANSFORM_H
#define SOLUTIONTRANSFORM_H

#include <memory>
#include "BaseSolution.h"
#include "../modelvisitor/ModelVisitor.h"
#include "../builder/DirectorCreator.h"
#include "../object/AbstractObject.h"

template<typename Type>
concept ConstructibleDouble = std::is_constructible_v<Type, double, double, double>;

class SolutionTransform : public BaseSolution
{
public:
    SolutionTransform() noexcept;
    explicit SolutionTransform(const std::shared_ptr<ModelVisitor> visitor) noexcept;

    template<typename visitor>
        requires Derivative<visitor, ModelVisitor> && NotAbstract<visitor> && ConstructibleDouble<visitor>
    void set_visitor(double x, double y, double z) { this->visitor = std::make_shared<visitor>(x, y, z); }

    void transform(std::shared_ptr<AbstractObject>& object) const;

protected:
    std::shared_ptr<ModelVisitor> visitor;
};

#endif // SOLUTIONTRANSFORM_H
