#ifndef LOADER_H
#define LOADER_H

#include <memory>
#include <string>
#include "../object/AbstractObject.h"
#include "../builder/BaseDirector.h"

class Loader
{
public:
    Loader();
    ~Loader() = default;

    static std::shared_ptr<AbstractObject> load(std::shared_ptr<BaseDirector> director);
};

#endif // LOADER_H
