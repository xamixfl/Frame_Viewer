#ifndef CREATE_DRAWER_FACTORY_H
#define CREATE_DRAWER_FACTORY_H

#include "abstract_drawer_factory.h"
#include "concepts.h"

class CreateDrawerFactory
{
public:
	template<Derivative<AbstractDrawerFactory> TFactory, class ...Args>
	requires NotAbstract<TFactory>
	static std::unique_ptr<BaseDrawer> create(Args &&...args)
	{
		std::shared_ptr<AbstractDrawerFactory> factory = std::make_shared<TFactory>(std::forward<Args>(args)...);
		return factory->createDrawer();
	}
};


#endif //CREATE_DRAWER_FACTORY_H
