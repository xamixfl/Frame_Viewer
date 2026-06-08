#ifndef QT_DRAWER_H
#define QT_DRAWER_H


#include <QGraphicsScene>
#include <memory>
#include "base_drawer.h"

class QtDrawer: public BaseDrawer
{
public:
	QtDrawer() = delete;

	explicit QtDrawer(std::weak_ptr<QGraphicsScene> &scene);

	void clear() override;
	void drawLine(const Point2D &p1, const Point2D &p2) override;

private:
	std::weak_ptr<QGraphicsScene> scene;

};


#endif //QT_DRAWER_H
