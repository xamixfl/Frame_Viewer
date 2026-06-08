#ifndef BASEDIRECTOR_HPP
#define BASEDIRECTOR_HPP
#include <memory>

#include "../../../BaseObject/BaseObject.hpp"

class BaseDirector
{
public:
    virtual ~BaseDirector() = default;

    BaseDirector(const BaseDirector&) = delete;
    BaseDirector& operator=(const BaseDirector&) = delete;

    [[nodiscard]] virtual std::shared_ptr<BaseObject> create() = 0;

protected:
    BaseDirector() noexcept = default;
};

#endif //BASEDIRECTOR_HPP
