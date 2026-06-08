#include <cmath>
#include "draw_visitor.h"


DrawVisitor::DrawVisitor(std::shared_ptr<DrawerFactory> fact, std::shared_ptr<Camera> cam, int _width, int _height)
    : camera(std::move(cam)), factory(std::move(fact)), width(std::move(_width)), height(std::move(_height))
{}

Point DrawVisitor::get_proection(const Point &point)
{
    Point pos = camera->get_position();
    Point tar = camera->get_target();
    Point up_hint = camera->get_up();

    Point forward = (tar - pos).normalize();
    Point right = (forward.crossproduct(up_hint)).normalize();
    Point up = right.crossproduct(forward);

    Point v = point - pos;

    double x = v.dotproduct(right);
    double y = v.dotproduct(up);
    double z = v.dotproduct(forward);

    double fov = 600.0; 
    
    double factor = (z > 0.1) ? fov / z : 0;

    double sx = x * factor;
    double sy = y * factor;

    double cx = width / 2.0;
    double cy = height / 2.0;

    return Point(cx + sx, cy - sy, z);
}

void DrawVisitor::visit(ModelImpl &obj)
{
    std::vector<Point> points = obj.get_points();
    
    Point cam_pos = camera->get_position();

    std::vector<Edge> edges = obj.get_visible_edges(cam_pos);

    std::shared_ptr<Drawer> drawer = factory->create_drawer();

    for (auto &edge : edges)
    {
        Point first = get_proection(points[edge.get_first()]);
        Point second = get_proection(points[edge.get_second()]);

        if (first.get_z() > 0.1 && second.get_z() > 0.1)
        {
            drawer->draw_line(first, second);
        }
    }
}

void DrawVisitor::visit(CameraImpl &obj)
{
    return;
}
