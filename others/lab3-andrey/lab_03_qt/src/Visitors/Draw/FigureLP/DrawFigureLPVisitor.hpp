#ifndef DRAWFIGURELPVISITOR_HPP
#define DRAWFIGURELPVISITOR_HPP

#include "../../BaseDrawTemplateVisitor.hpp"
#include "../../../Drawer/Factory/AbstractDrawerFactory.hpp"
#include "../../../HLR/BaseHLRStrategy.hpp"
#include "../../../HLR/AllEdgesStrategy.hpp"

class AbstractFigureLP;

class DrawFigureLPVisitor : public BaseDrawTemplateVisitor
{
public:
    DrawFigureLPVisitor() = delete;

    explicit DrawFigureLPVisitor(
        const std::shared_ptr<BaseCameraTransformer>&  transformer,
        const std::shared_ptr<AbstractDrawerFactory>&  factory,
        std::shared_ptr<BaseHLRStrategy>               hlrStrategy
            = std::make_shared<AllEdgesStrategy>())
        : _transformer(transformer)
        , _drawer(factory->createDrawer())
        , _hlr(std::move(hlrStrategy))
    {}

    ~DrawFigureLPVisitor() override = default;

    void visit(const AbstractFigureLP& figure) const override;

private:
    std::shared_ptr<BaseCameraTransformer> _transformer;
    std::shared_ptr<BaseDrawer>            _drawer;
    std::shared_ptr<BaseHLRStrategy>       _hlr;
};

#endif //DRAWFIGURELPVISITOR_HPP
