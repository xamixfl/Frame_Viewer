//
// Created as part of Drawer factory refactoring
//

#include "QtDrawerFactory.hpp"
#include "../Drawer/QtDrawer.hpp"

std::shared_ptr<BaseDrawer> QtDrawerFactory::createDrawer() const
{
    return std::make_shared<QtDrawer>(_scene, _pen);
}
