#include "factory/QtDrawerFactory.h"
#include "factory/QtDrawer.h"

std::unique_ptr<BaseDrawer> QtDrawerFactory::createDrawer() {
    return std::make_unique<QtDrawer>(_scene);
}
