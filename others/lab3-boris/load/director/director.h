#ifndef DIRECTOR_H__
#define DIRECTOR_H__

#include "builder.h"


class Director
{
public:
    Director() = default;
    virtual ~Director() = 0;

    virtual std::shared_ptr<Object> create() = 0;

protected:
    std::shared_ptr<Builder> builder;
};

#endif
