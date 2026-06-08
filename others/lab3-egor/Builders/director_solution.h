#ifndef DIRECTOR_SOLUTION_H
#define DIRECTOR_SOLUTION_H

#include <memory>
#include <carcass_model_creator.h>
#include <map>
#include <functional>
#include "concepts.h"

#include "model_data_source.h"

class CreateCarcassModelCreator
{
public:
	template<typename T>
	static std::shared_ptr<CarcassModelCreator> create(std::shared_ptr<ModelDataSource> dataSource)
	{
		return std::make_shared<T>(std::move(dataSource));
	}
};

class CarcassModelDirectorSolution
{
public:
	using CarcassModelCreatorMaker = std::shared_ptr<CarcassModelCreator>(&)(std::shared_ptr<ModelDataSource>);
	using CallBackMap = std::map<size_t, CarcassModelCreatorMaker>;

	CarcassModelDirectorSolution() = default;
	CarcassModelDirectorSolution(std::initializer_list<std::pair<size_t, CarcassModelCreatorMaker>> ilist);

	bool registrate(size_t id, CarcassModelCreatorMaker maker);
	bool check(size_t id);

	std::shared_ptr<CarcassModelCreator> create(size_t id, std::shared_ptr<ModelDataSource> dataSource);

	static std::shared_ptr<CarcassModelDirectorSolution>
	makeSolution(std::initializer_list<std::pair<size_t, CarcassModelCreatorMaker>> ilist)
	{
		return std::make_shared<CarcassModelDirectorSolution>(ilist);
	}

private:
	CallBackMap directors;
};


#endif //DIRECTOR_SOLUTION_H
