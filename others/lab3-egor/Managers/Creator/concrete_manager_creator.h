#ifndef CONCRETE_MANAGER_CREATOR_H
#define CONCRETE_MANAGER_CREATOR_H

#include "manager_creator.h"
#include "concepts.h"

template<typename TManager>
requires NotAbstract<TManager>
class ConcreteManagerCreator: public ManagerCreator
{
protected:
	std::shared_ptr<BaseManager> createManager() override
	{
		class Proxy: public TManager
		{
		};
		return std::make_shared<Proxy>();
//		return std::make_shared<TManager>();
	}
};




#endif //CONCRETE_MANAGER_CREATOR_H
