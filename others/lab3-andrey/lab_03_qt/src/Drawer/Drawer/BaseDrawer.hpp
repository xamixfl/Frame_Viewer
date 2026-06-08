//
// Refactored: removed setScene(), setPen(), BaseColorParameters dependency
//

#ifndef BASEDRAWER_HPP
#define BASEDRAWER_HPP

#include "../../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Point/Points.hpp"

class BaseDrawer
{
public:
    BaseDrawer() = default;
    virtual ~BaseDrawer() = default;

    virtual void drawLine(const Point& p1, const Point& p2) = 0;
    virtual void clear() = 0;
};

#endif //BASEDRAWER_HPP
