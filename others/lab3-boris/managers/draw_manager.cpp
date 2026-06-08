#include "draw_manager.h"


DrawManager::DrawManager(std::shared_ptr<DrawerFactory> _fact, int _width, int _height)
    : fact(std::move(_fact)), width(std::move(_width)), height(std::move(_height))
{}

void DrawManager::draw(std::shared_ptr<Object> obj, std::shared_ptr<Camera> cam)
{
    std::shared_ptr<DrawVisitor> v = std::make_shared<DrawVisitor>(fact, cam, width, height);
    obj->accept(v);
}

void DrawManager::clear_scene()
{
    std::shared_ptr<Drawer> drawer = fact->create_drawer();
    drawer->clear_scene();
}
