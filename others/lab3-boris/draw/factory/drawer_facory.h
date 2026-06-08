#ifndef DRAWER_FACTORY_H__
#define DRAWER_FACTORY_H__

#include <memory>
#include "drawer.h"


class DrawerFactory
{
public:
    DrawerFactory() = default;
    virtual ~DrawerFactory() = 0;

    virtual std::shared_ptr<Drawer> create_drawer() = 0;
};

#endif
