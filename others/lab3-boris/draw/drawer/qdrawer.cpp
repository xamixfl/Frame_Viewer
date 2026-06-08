#include "qdrawer.h"


QDrawer::QDrawer(std::shared_ptr<QGraphicsScene> _scene, QPointer<QGraphicsView> _view)
    : scene(std::move(_scene)), view(std::move(_view))
{}

void QDrawer::draw_line(const Point &first, const Point &second)
{
    scene->addLine(first.get_x(), first.get_y(), second.get_x(), second.get_y());
}

void QDrawer::clear_scene()
{
    scene->clear();
}
