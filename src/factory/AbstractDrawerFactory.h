#ifndef ABSTRACTDRAWERFACTORY_H
#define ABSTRACTDRAWERFACTORY_H

#include <memory>

class BaseDrawer;

class AbstractDrawerFactory {
public:
    virtual ~AbstractDrawerFactory() = default;

    [[nodiscard]] virtual std::unique_ptr<BaseDrawer> createDrawer() = 0;
};

#endif // ABSTRACTDRAWERFACTORY_H
