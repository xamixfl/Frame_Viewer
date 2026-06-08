#ifndef MANAGER_CREATOR_H
#define MANAGER_CREATOR_H

#include <memory>
#include "base_manager.h"

class ManagerCreator
{
public:
	virtual ~ManagerCreator() = default;
	std::shared_ptr<BaseManager> getManager();

protected:
	virtual std::shared_ptr<BaseManager> createManager() = 0;
private:
	std::shared_ptr<BaseManager> manager{nullptr};
};


#endif //MANAGER_CREATOR_H
