#include "DrawCommand.h"
#include "../draw/DrawAll.h"
#include "../draw/QtFactory.h"

void Draw::execute()
{
    auto objs = this->proxy.scene->get_objects();
    std::shared_ptr<Camera> camera = this->proxy.scene->get_main_camera();

    this->proxy.draw->set_camera(camera);

    for (auto& elem : objs)
    {
        this->proxy.draw->accept(elem);
    }
}
