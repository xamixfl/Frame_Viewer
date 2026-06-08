#ifndef DRAW_MANAGER_H__
#define DRAW_MANAGER_H__

#include "draw_visitor.h"
#include "base_manager.h"
#include "concepts.h"


class DrawManager : public BaseManager
{
public:
    DrawManager() = default;
    explicit DrawManager(std::shared_ptr<DrawerFactory> _fact, int _width, int _height);
    ~DrawManager() override = default;

    void draw(std::shared_ptr<Object> obj, std::shared_ptr<Camera> cam);
    void clear_scene();

private:
    std::shared_ptr<DrawerFactory> fact;
    int width, height;
};

#endif
