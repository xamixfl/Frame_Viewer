#include "MoveObjectVisitor.hpp"

#include "../../../BaseObject/Camera/BaseCameraPTUImpl.hpp"
#include "../../../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/AbstractFigureLP.hpp"
#include "../../../Exceptions/Visitors/VisitorException.hpp"

MoveObjectVisitor::MoveObjectVisitor(const std::shared_ptr<BaseTransform>& transform)
{
    const auto tfm = dynamic_pointer_cast<Mover>(transform);

    if (tfm == nullptr)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorVisitor_invalid_data(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    _transform = tfm;
}

void MoveObjectVisitor::visit(AbstractFigureLP& figure)
{
    figure.transform(*_transform);
}

void MoveObjectVisitor::visit(BaseCameraPTUImpl& camera)
{
    camera.transform(*_transform);
}
