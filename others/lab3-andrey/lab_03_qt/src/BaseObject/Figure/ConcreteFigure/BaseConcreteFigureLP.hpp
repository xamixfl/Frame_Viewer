//
// Created by nuelex on 09/05/25.
//

#ifndef BASECONCRETEFIGURE_HPP
#define BASECONCRETEFIGURE_HPP

#include "../Figure.hpp"
#include "../../../Transforms/Transforms.hpp"
#include "../../../Visitors/Draw/FigureLP/DrawFigureLPVisitor.hpp"
#include "ConcreteFigureLP/FigureLP/AbstractFigureLP.hpp"
#include "ConcreteFigureLP/Links/Links.hpp"
#include "ConcreteFigureLP/Point/Points.hpp"

class BaseConcreteFigureLP : public Figure
{
protected:
    std::shared_ptr<AbstractFigureLP> figureLP_{};

public:
    BaseConcreteFigureLP() = default;
    ~BaseConcreteFigureLP() override = default;

    std::shared_ptr<AbstractFigureLP> getFigureLP() const {
        return figureLP_;
    }

    void accept(const BaseDrawTemplateVisitor &visitor) override {}
    void accept(BaseTransformVisitor &visitor) override {}
};



#endif //BASECONCRETEFIGURE_HPP
