#include "qt_drawer_factory.h"
#include "qt_drawer.h"

QtDrawerFactory::QtDrawerFactory(std::shared_ptr<QGraphicsScene> scene)
{
	this->scene = scene;
}

std::unique_ptr<BaseDrawer> QtDrawerFactory::createDrawer()
{
	return std::make_unique<QtDrawer>(scene);
}

