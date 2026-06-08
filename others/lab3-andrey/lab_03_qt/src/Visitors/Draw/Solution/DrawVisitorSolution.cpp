#include "DrawVisitorSolution.hpp"

#include "../../../BaseObject/Composite/CompositeObject.hpp"
#include "../../../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/ConcreteFigureLP.hpp"
#include "../../../Exceptions/Visitors/VisitorException.hpp"
#include "../FigureLP/DrawFigureLPVisitor.hpp"

DrawVisitorSolution::DrawVisitorSolution()
{
    try
    {
        reg(std::make_shared<ConcreteFigureLP>(),
            std::make_shared<ConcreteDrawVisitorCreator<DrawFigureLPVisitor>>());
        reg(std::make_shared<CompositeObject>(),
            std::make_shared<ConcreteDrawVisitorCreator<DrawFigureLPVisitor>>());
    }
    catch (std::bad_alloc&)
    {
        const time_t t = time(nullptr);
        throw ErrorVisitor_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
}

void DrawVisitorSolution::reg(const std::shared_ptr<BaseObject>&        object,
                               const std::shared_ptr<DrawVisitorCreator>& creator)
{
    _creators[object] = creator;
}

std::shared_ptr<BaseDrawTemplateVisitor> DrawVisitorSolution::createDrawTemplateVisitor(
    const std::shared_ptr<BaseObject>&            object,
    const std::shared_ptr<BaseCameraTransformer>& transformer,
    const std::shared_ptr<AbstractDrawerFactory>& factory,
    const std::shared_ptr<BaseHLRStrategy>&       hlr)
{
    const auto iter = _creators.find(object);
    if (iter == _creators.end())
    {
        const time_t t = time(nullptr);
        throw ErrorVisitor_invalid_data(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    try
    {
        return iter->second->createDrawVisitor(transformer, factory, hlr);
    }
    catch (std::bad_alloc&)
    {
        const time_t t = time(nullptr);
        throw ErrorVisitor_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
}
