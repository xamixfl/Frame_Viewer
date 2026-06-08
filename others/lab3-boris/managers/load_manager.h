#ifndef LOAD_MANAGER_H__
#define LOAD_MANAGER_H__

#include "base_manager.h"
#include "concepts.h"
#include "director_solution.h"


template<typename Class>
concept ValidLoader = ValidClass<Class, Loader>;


class LoadManager : public BaseManager
{
public:
    LoadManager() = default;
    explicit LoadManager(std::shared_ptr<DirectorSolution> _solution);
    ~LoadManager() override = default;

    template<ValidLoader TLoader>
    std::shared_ptr<Object> load(std::size_t id, std::string filename)
    {
        std::shared_ptr<Loader> loader = std::make_shared<TLoader>(filename);
        std::shared_ptr<DirectorCreator> creator = solution->create(id);

        if (!creator)
        {
            throw std::runtime_error("Director creator for id " + std::to_string(id) + " not found.");
        }

        std::shared_ptr<Director> director = creator->create_director(loader);
        return director->create();
    }

private:
    std::shared_ptr<DirectorSolution> solution;
};

#endif
