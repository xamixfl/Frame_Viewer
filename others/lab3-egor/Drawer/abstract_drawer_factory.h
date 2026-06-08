#ifndef ABSTRACT_DRAWER_FACTORY_H
#define ABSTRACT_DRAWER_FACTORY_H

#include <memory>
#include "base_drawer.h"

class AbstractDrawerFactory
{
public:
	virtual ~AbstractDrawerFactory() = default;

	virtual std::unique_ptr<BaseDrawer> createDrawer() = 0;
};


#endif //ABSTRACT_DRAWER_FACTORY_H
