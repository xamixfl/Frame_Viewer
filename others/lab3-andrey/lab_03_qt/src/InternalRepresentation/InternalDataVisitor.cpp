#include "InternalDataVisitor.hpp"

#include "../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/AbstractFigureLP.hpp"

void InternalDataVisitor::visit(const AbstractFigureLP& figure) const
{
    _points.clear();
    _links.clear();

    const auto& points = figure.getPoints();
    const auto& links  = figure.getLinks();

    auto pIter = points.CreateConstIterator();
    for (pIter.First(); !pIter.IsDone(); pIter.Next())
        _points.push_back(*pIter.Current());

    auto lIter = links.CreateConstIterator();
    for (lIter.First(); !lIter.IsDone(); lIter.Next())
        _links.emplace_back(lIter.Current()->GetBeginID(),
                            lIter.Current()->GetEndID());
}
