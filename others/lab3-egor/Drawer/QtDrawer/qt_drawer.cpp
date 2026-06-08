#include "qt_drawer.h"

QtDrawer::QtDrawer(std::weak_ptr<QGraphicsScene> &scene)
{
	this->scene = scene;
}

void QtDrawer::clear()
{
	scene.lock()->clear();
}

void QtDrawer::drawLine(const Point2D &p1, const Point2D &p2)
{
	scene.lock()->addLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}