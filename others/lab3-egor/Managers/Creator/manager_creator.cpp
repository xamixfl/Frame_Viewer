#include "manager_creator.h"

std::shared_ptr<BaseManager> ManagerCreator::getManager()
{
	if (!manager)
		manager = createManager();

	return manager;
}
