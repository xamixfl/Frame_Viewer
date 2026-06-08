#include "DrawFigureLPVisitor.hpp"

#include "../../../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/AbstractFigureLP.hpp"

void DrawFigureLPVisitor::visit(const AbstractFigureLP& figure) const
{
    const auto& links   = figure.getLinks();
    const auto& points  = figure.getPoints();
    const auto& faces   = figure.getFaces();

    const auto visible = _hlr->visibleEdges(links, points, faces, _transformer);

    auto iter = links.CreateConstIterator();
    size_t edgeIdx = 0;
    size_t visIdx  = 0;

    for (iter.First(); !iter.IsDone(); iter.Next(), ++edgeIdx)
    {
        while (visIdx < visible.size() && visible[visIdx] < edgeIdx) ++visIdx;
        if (visIdx >= visible.size() || visible[visIdx] != edgeIdx) continue;

        try
        {
            _drawer->drawLine(
                _transformer->transform(points[iter.Current()->GetBeginID()]),
                _transformer->transform(points[iter.Current()->GetEndID()])
            );
        }
        catch (...)
        {
        }
    }
}
