#ifndef DIRECTOR_SOLUTION_H__
#define DIRECTOR_SOLUTION_H__

#include <map>
#include <initializer_list>
#include "director_creator.h"
#include "loader.h"


class DirectorSolution
{
public:
    using CreateCreator = std::shared_ptr<DirectorCreator>(&)();
    using CallBackMap = std::map<std::size_t, CreateCreator>;

    DirectorSolution() = default;
    DirectorSolution(std::initializer_list<std::pair<std::size_t, CreateCreator>> list);
    ~DirectorSolution() = default;

    bool registrate(std::size_t id, CreateCreator creator_fn);
    bool check(std::size_t id);

    std::shared_ptr<DirectorCreator> create(std::size_t id);

private:
    CallBackMap callbacks;
};

#endif
