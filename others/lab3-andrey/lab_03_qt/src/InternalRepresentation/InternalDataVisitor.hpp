#ifndef INTERNALDATAVISITOR_HPP
#define INTERNALDATAVISITOR_HPP

#include "../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Point/Points.hpp"
#include "../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Links/Links.hpp"
#include "../Visitors/BaseDrawTemplateVisitor.hpp"

class AbstractFigureLP;

class InternalDataVisitor : public BaseDrawTemplateVisitor
{
public:
    InternalDataVisitor() = default;
    ~InternalDataVisitor() override = default;

    void visit(const AbstractFigureLP& figure) const override;

    [[nodiscard]] const std::vector<Point>& getPointsList() const noexcept { return _points; }
    [[nodiscard]] const std::vector<std::pair<size_t,size_t>>& getLinksList() const noexcept { return _links; }

private:
    mutable std::vector<Point>                      _points;
    mutable std::vector<std::pair<size_t, size_t>>  _links;
};

#endif //INTERNALDATAVISITOR_HPP
