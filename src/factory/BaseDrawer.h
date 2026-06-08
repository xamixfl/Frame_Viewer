#ifndef BASEDRAWER_H
#define BASEDRAWER_H

#include "data/Point.h"

class BaseDrawer {
public:
    virtual ~BaseDrawer() = default;

    virtual void drawLine(const Point& p1, const Point& p2) = 0;
    virtual void clear() = 0;
};

#endif // BASEDRAWER_H
