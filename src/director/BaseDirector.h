#ifndef BASEDIRECTOR_H
#define BASEDIRECTOR_H

#include <memory>
#include <string>

#include "composite/BaseObject.h"

class BaseDirector {
public:
    using ObjectPtr = std::shared_ptr<BaseObject>;

    virtual ~BaseDirector() = default;

    BaseDirector(const BaseDirector&) = delete;
    BaseDirector& operator=(const BaseDirector&) = delete;

    [[nodiscard]] virtual ObjectPtr construct(const std::string& filename) = 0;

protected:
    BaseDirector() noexcept = default;
};

#endif 
