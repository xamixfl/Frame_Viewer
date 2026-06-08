#ifndef MANAGER_SOLUTION_H
#define MANAGER_SOLUTION_H


#include <memory>
#include "manager_creator.h"
#include "concrete_manager_creator.h"

class ManagerSolution
{
public:
	template<typename TManager>
	requires NotAbstract<TManager>
	static std::shared_ptr<TManager> getManager()
	{
		return std::static_pointer_cast<TManager>(getCreator<TManager>()->getManager());
	}

private:
	ManagerSolution() = default;

	template<typename TManager>
	requires NotAbstract<TManager>
	static std::shared_ptr<ManagerCreator> getCreator()
	{
		static auto creator = std::make_shared<ConcreteManagerCreator<TManager>>();
		return creator;
	}
};


#endif //MANAGER_SOLUTION_H
