//
// Created by nuelex on 08/05/25.
//

#include "Points.hpp"
#include "../../../../../Exceptions/Figure/PointsException.hpp"

#include <cmath>

void Points::AddPoint(const double& x, const double& y, const double& z)
{
    try
    {
        points.emplace_back(x, y, z);
    }
    catch (std::bad_alloc& e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorPoints_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

Points& Points::operator=(const Points& points_arg)
{
    points = points_arg.points;
    return *this;
}

void Point::rotateX(const double angle)
{
    const double tmp_point_y = y;

    this->SetY(y * cos(angle) - z * sin(angle));
    this->SetZ(tmp_point_y * sin(angle) + z * cos(angle));
}

void Point::rotateY(const double angle)
{
    const double tmp_point_x = x;

    this->SetX(x * cos(angle) + z * sin(angle));
    this->SetZ(z * cos(angle) - tmp_point_x * sin(angle));
}

void Point::rotateZ(const double angle)
{
    const double tmp_point_x = x;

    this->SetX(x * cos(angle) - y * sin(angle));
    this->SetY(tmp_point_x * sin(angle) + y * cos(angle));
}

Point Point::operator-() const noexcept
{
    const Point tmp{-this->GetX(), -this->GetY(), -this->GetZ()};

    return tmp;
}
