#ifndef FIGURELPBUILDER_HPP
#define FIGURELPBUILDER_HPP
#include <memory>

#include "BaseFigureLPBuilder.hpp"
#include "../../../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/AbstractFigureLP.hpp"
#include "../../../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/FigureLP/FigureLP.hpp"


class FigureLPBuilder final : public BaseFigureLPBuilder
{
public:
    explicit FigureLPBuilder(std::shared_ptr<BaseLPReader> reader) noexcept;
    ~FigureLPBuilder() override = default;

    void build() override;

    [[nodiscard]] std::shared_ptr<AbstractFigureLP> getResult() noexcept;

private:
    std::shared_ptr<FigureLP> _figure;

    void _checkReader() const;
    void _initFigure();
    void _readPoints();
    void _readLinks();
    void _readFaces();
};



#endif //FIGURELPBUILDER_HPP
