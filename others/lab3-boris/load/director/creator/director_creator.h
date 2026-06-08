#ifndef DIRECTOR_CREATOR_H__
#define DIRECTOR_CREATOR_H__

#include "director.h"
#include "loader.h"


class DirectorCreator
{
public:
    DirectorCreator() = default;
    virtual ~DirectorCreator() = 0;

    virtual std::shared_ptr<Director> create_director(std::shared_ptr<Loader> loader) const = 0;
};

#endif
