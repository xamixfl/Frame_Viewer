#ifndef QT_DRAWER_FACTORY_H
#define QT_DRAWER_FACTORY_H

#include "abstract_drawer_factory.h"
#include <QGraphicsScene>


class QtDrawerFactory: public AbstractDrawerFactory
{
public:
	explicit QtDrawerFactory(std::shared_ptr<QGraphicsScene> scene);
	std::unique_ptr<BaseDrawer> createDrawer() override;

private:
	std::weak_ptr<QGraphicsScene> scene{};
};


#endif //QT_DRAWER_FACTORY_H
