#include "qfactory.h"


QFactory::QFactory(std::shared_ptr<QGraphicsScene> _scene, QPointer<QGraphicsView> _view)
    : scene(std::move(_scene)), view(std::move(_view))
{}

std::shared_ptr<Drawer> QFactory::create_drawer()
{
    return std::make_shared<QDrawer>(scene, view);
}
