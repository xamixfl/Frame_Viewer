#include "FigureLPDirector.hpp"

#include "../../../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/ConcreteFigureLP.hpp"

FigureLPDirector::FigureLPDirector(std::shared_ptr<FigureLPBuilder> builder) noexcept
    : _builder(std::move(builder))
{
}

std::shared_ptr<BaseObject> FigureLPDirector::create()
{
    _builder->build();
    return std::make_shared<ConcreteFigureLP>(_builder->getResult());
}
