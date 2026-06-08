#include "data_source_solution.h"

#include <utility>
#include "model_exception.h"

DataSourceSolution::DataSourceSolution(std::initializer_list<std::pair<size_t, SourceCreatorMaker>> ilist)
{
	for (auto &pair : ilist)
		this->registrate(pair.first, pair.second);
}

bool DataSourceSolution::registrate(size_t id, SourceCreatorMaker maker)
{
	return dataSourceCreators.insert(CallBackMap::value_type(id, maker)).second;
}

bool DataSourceSolution::check(size_t id)
{
	return dataSourceCreators.erase(id) == 1;
}

std::shared_ptr<DataSourceCreator> DataSourceSolution::create(size_t id)
{
	auto it = dataSourceCreators.find(id);

	return it != dataSourceCreators.end() ? std::shared_ptr<DataSourceCreator>(it->second()) : nullptr;
}
