#ifndef DATA_SOURCE_SOLUTION_H
#define DATA_SOURCE_SOLUTION_H

#include "data_source.h"
#include "data_source_creator.h"
#include "concrete_data_source_creator.h"
#include "concepts.h"
#include "map"

class CreateDataSourceCreator
{
public:
	virtual ~CreateDataSourceCreator() = default;

	template<Derivative<ModelDataSource> TDataSource>
	requires NotAbstract<TDataSource>
	static std::shared_ptr<DataSourceCreator> create()
	{
		return std::make_shared<ConcreteDataSourceCreator<TDataSource>>();
	}
};

class DataSourceSolution
{
public:
	using SourceCreatorMaker = std::shared_ptr<DataSourceCreator> (&)();
	using CallBackMap = std::map<size_t, SourceCreatorMaker>;

public:
	DataSourceSolution() = default;
	DataSourceSolution(std::initializer_list<std::pair<size_t, SourceCreatorMaker>> ilist);

	bool registrate(size_t id, SourceCreatorMaker maker);
	bool check(size_t id);

	std::shared_ptr<DataSourceCreator> create(size_t id);

	static std::shared_ptr<DataSourceSolution>
	makeSolution(std::initializer_list<std::pair<size_t, SourceCreatorMaker>> ilist)
	{
		return std::make_shared<DataSourceSolution>(ilist);
	}

private:
	CallBackMap dataSourceCreators;
};


#endif //DATA_SOURCE_SOLUTION_H