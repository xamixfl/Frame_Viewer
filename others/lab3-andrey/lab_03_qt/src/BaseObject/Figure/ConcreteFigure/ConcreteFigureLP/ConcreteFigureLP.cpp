//
// Created by nuelex on 09/05/25.
//

#include "ConcreteFigureLP.hpp"


void ConcreteFigureLP::accept(const BaseDrawTemplateVisitor& visitor)
{
    visitor.visit(*figureLP_);
}
