#include "RotateObjectVisitor.hpp"

#include "../../../BaseObject/Camera/BaseCameraPTUImpl.hpp"
#include "../../../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/AbstractFigureLP.hpp"
#include "../../../Exceptions/Visitors/VisitorException.hpp"


RotateObjectVisitor::RotateObjectVisitor(const std::shared_ptr<BaseTransform>& transform)
{
    const auto tfm = dynamic_pointer_cast<Rotater>(transform);

    if (tfm == nullptr)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorVisitor_invalid_data(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    _transform = tfm;
}

void RotateObjectVisitor::visit(AbstractFigureLP& figure)
{
    figure.transform(*_transform);
}

void RotateObjectVisitor::visit(BaseCameraPTUImpl& camera)
{
    camera.transform(*_transform);
}
