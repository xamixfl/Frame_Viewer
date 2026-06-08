#include "DrawVisitor.h"
#include "../object/camera/Camera.h"
#include "../object/carcas/Carcas.h"

DrawVisitor::DrawVisitor() {}

static double dotproduct(const Point& left, const Point& right)
{
    return left.get_x() * right.get_x() + left.get_y() * right.get_y() + left.get_z() * right.get_z();
}

Point DrawVisitor::toCameraSpace(const Point& W)
{
    Point rel = W - camera->center;
    float cx = dotproduct(rel, camera->right);
    float cy = dotproduct(rel, camera->up);
    float cz = dotproduct(rel, camera->forward);
    return Point(cx, cy, cz);
}

Point DrawVisitor::get_proection(const Point& point)
{
    Point copy = point;
    Point center = camera->center;
    Point right = camera->right;
    Point up = camera->up;
    Point forward = camera->forward;

    copy.move(center.get_x(), -center.get_y(), center.get_z());

    float length = sqrt(copy.get_x() * copy.get_x() + copy.get_y() * copy.get_y() + copy.get_z() * copy.get_z());
    if (fabs(length) > 0.001)
    {
        copy.set_x(copy.get_x() / length);
        copy.set_y(copy.get_y() / length);
        copy.set_z(copy.get_z() / length);
    }

    copy.move(-center.get_x(), -center.get_y(), -center.get_z());

    float dx = dotproduct(copy, right);
    float dy = dotproduct(copy, up);
    float dz = dotproduct(copy, forward);

    copy.set_x(dx);
    copy.set_y(dy);
    copy.set_z(dz);

    copy.move(center.get_x(), center.get_y(), center.get_z());

    copy.set_x((copy.get_x() + 1) * width / 2);
    copy.set_y((1 - copy.get_y()) * height / 2);

    return copy;
}
