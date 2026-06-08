#ifndef CONCRETE_DIRECTOR_CREATOR_H__
#define CONCRETE_DIRECTOR_CREATOR_H__

#include "director_creator.h"
#include "concepts.h"
#include "builder.h"


template<typename TClass>
concept ValidDirector = ValidClass<TClass, Director>;

template<typename TClass>
concept ValidBuilder = ValidClass<TClass, Builder>;


template<ValidDirector TDirector, ValidBuilder TBuilder>
class ConcreteDirectorCreator : public DirectorCreator
{
public:
    ConcreteDirectorCreator() = default;
    ~ConcreteDirectorCreator() override = default;

    std::shared_ptr<Director> create_director(std::shared_ptr<Loader> loader) const override
    {
        std::shared_ptr<Builder> builder = std::make_shared<TBuilder>(loader);
        return std::make_shared<TDirector>(builder);
    }
};

#endif
