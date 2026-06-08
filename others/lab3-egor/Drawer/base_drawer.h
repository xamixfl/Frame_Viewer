#ifndef BASE_DRAWER_H
#define BASE_DRAWER_H

#include "point.h"
#include "point_2_d.h"

class BaseDrawer
{
public:
	BaseDrawer() = default;
	virtual ~BaseDrawer() = default;

	virtual void clear() = 0;
	virtual void drawLine(const Point2D &p1, const Point2D &p2) = 0;
};


#endif //BASE_DRAWER_H
