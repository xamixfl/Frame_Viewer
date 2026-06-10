#ifndef BASECREATOR_H
#define BASECREATOR_H

#include <memory>

#include "composite/BaseObject.h"
#include "director/BaseDirector.h"

class BaseCreator {
public:
    using ObjectPtr = std::shared_ptr<BaseObject>;

    virtual ~BaseCreator() = default;

    [[nodiscard]] virtual std::unique_ptr<BaseDirector> createDirector() = 0;
};

#endif 
