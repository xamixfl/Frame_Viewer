#ifndef BASEDRAWER_H
#define BASEDRAWER_H

#include "data/Point.h"
#include "bridge/BaseModelImpl.h"

class BaseDrawer {
public:
    virtual ~BaseDrawer() = default;

    virtual void drawLine(const Point& p1, const Point& p2) = 0;
    virtual void clear() = 0;

    virtual void setColor(float r, float g, float b) = 0; 
    virtual void drawPolygon(const std::vector<Point>& vertices, const Material& mat) = 0;
};

#endif
