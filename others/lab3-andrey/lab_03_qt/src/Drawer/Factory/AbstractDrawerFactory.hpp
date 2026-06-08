#ifndef ABSTRACTDRAWERFACTORY_HPP
#define ABSTRACTDRAWERFACTORY_HPP

#include <memory>
#include "../Drawer/BaseDrawer.hpp"

class AbstractDrawerFactory
{
public:
    AbstractDrawerFactory() = default;
    virtual ~AbstractDrawerFactory() = default;

    [[nodiscard]] virtual std::shared_ptr<BaseDrawer> createDrawer() const = 0;
};

#endif //ABSTRACTDRAWERFACTORY_HPP
