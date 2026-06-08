#include "TriangleCarcas.h"

TriangleCarcas::TriangleCarcas(std::vector<Point>& points, const std::vector<Triangle>& indices)
{
    this->points = points;
    this->indices = indices;
    revalue_center();
}

std::vector<Point>& TriangleCarcas::get_points()
{
    return points;
}

bool TriangleCarcas::add_point(const Point& p)
{
    points.push_back(p);
    revalue_center();
    return true;
}

Point& TriangleCarcas::get_center()
{
    return center;
}

void TriangleCarcas::move_to_center()
{
    for (auto& point : this->points)
    {
        point.set_x(point.get_x() - this->center.get_x());
        point.set_y(point.get_y() - this->center.get_y());
        point.set_z(point.get_z() - this->center.get_z());
    }
}

void TriangleCarcas::move_back()
{
    for (auto& point : this->points)
    {
        point.set_x(point.get_x() + this->center.get_x());
        point.set_y(point.get_y() + this->center.get_y());
        point.set_z(point.get_z() + this->center.get_z());
    }
}

void TriangleCarcas::revalue_center()
{
    double x(0), y(0), z(0);

    for (auto& point : this->points)
    {
        x += point.get_x();
        y += point.get_y();
        z += point.get_z();
    }

    auto size = this->points.size();
    this->center.set_x(x / size);
    this->center.set_y(y / size);
    this->center.set_z(z / size);
}