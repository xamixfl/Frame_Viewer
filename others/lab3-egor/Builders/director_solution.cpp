#include "director_solution.h"

CarcassModelDirectorSolution::CarcassModelDirectorSolution(std::initializer_list<std::pair<size_t,
																						   CarcassModelCreatorMaker>> ilist)
{
	for (auto &pair : ilist)
		this->registrate(pair.first, pair.second);
}

bool CarcassModelDirectorSolution::registrate(size_t id, CarcassModelCreatorMaker maker)
{
	return directors.insert(CallBackMap::value_type(id, maker)).second;
}

bool CarcassModelDirectorSolution::check(size_t id)
{
	return directors.erase(id) == 1;
}

std::shared_ptr<CarcassModelCreator>
CarcassModelDirectorSolution::create(size_t id, std::shared_ptr<ModelDataSource> dataSource)
{
	auto it = directors.find(id);

	return it != directors.end() ? std::shared_ptr<CarcassModelCreator>(it->second(dataSource)) : nullptr;
}
