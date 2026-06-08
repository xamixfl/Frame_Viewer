#include "ScaleObjectVisitor.hpp"

#include "../../../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/AbstractFigureLP.hpp"
#include "../../../Exceptions/Visitors/VisitorException.hpp"

ScaleObjectVisitor::ScaleObjectVisitor(const std::shared_ptr<BaseTransform>& transform)
{
    const auto tfm = dynamic_pointer_cast<Scaler>(transform);

    if (tfm == nullptr)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorVisitor_invalid_data(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    _transform = tfm;
}

void ScaleObjectVisitor::visit(AbstractFigureLP& figure)
{
    figure.transform(*_transform);
}
