#ifndef DIRECTOR_CREATOR_MAKER_H__
#define DIRECTOR_CREATOR_MAKER_H__

#include "concrete_director_creator.h"


class DirectorCreatorMaker
{
public:
    DirectorCreatorMaker() = default;
    ~DirectorCreatorMaker() = default;

    template<ValidDirector TDirector, ValidBuilder TBuilder>
    static std::shared_ptr<DirectorCreator> create_director_creator()
    {
        return std::make_shared<ConcreteDirectorCreator<TDirector, TBuilder>>();
    }
};

#endif
