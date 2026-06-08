#include "QtDrawer.h"

QTDrawer::QTDrawer(std::shared_ptr<QGraphicsScene> scene, QGraphicsView* view)
    : scene(scene), view(view)
{}

void QTDrawer::draw_line(const Point& A, const Point& B)
{
    auto cont = this->view->contentsRect();

    this->scene->addLine(A.get_x(), A.get_y(),
                         B.get_x(), B.get_y());
}

void QTDrawer::clear_scene()
{
    this->scene->clear();
}
