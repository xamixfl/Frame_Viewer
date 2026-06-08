#ifndef BUILDER_H__
#define BUILDER_H__

#include <memory>
#include "loader.h"
#include "object.h"


class Builder
{
public:
    Builder() = default;
    virtual ~Builder() = 0;

    virtual void build() = 0;
    virtual std::shared_ptr<Object> get_result() = 0;

protected:
    std::shared_ptr<Loader> loader;
    std::shared_ptr<Object> obj;
};

#endif
