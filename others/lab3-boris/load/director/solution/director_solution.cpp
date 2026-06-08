#include "director_solution.h"


DirectorSolution::DirectorSolution(std::initializer_list<std::pair<std::size_t, CreateCreator>> list)
{
    for (auto &&elem : list)
    {
        registrate(elem.first, elem.second);
    }
}

bool DirectorSolution::registrate(std::size_t id, CreateCreator creator_fn)
{
    return callbacks.insert(CallBackMap::value_type(id, creator_fn)).second;
}

bool DirectorSolution::check(std::size_t id)
{
    return callbacks.erase(id) == 1;
}

std::shared_ptr<DirectorCreator> DirectorSolution::create(std::size_t id)
{
    auto it = callbacks.find(id);

    return it != callbacks.end() ? std::shared_ptr<DirectorCreator>(it->second()) : nullptr;
}
