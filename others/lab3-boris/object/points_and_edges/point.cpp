#include <cmath>
#include "point.h"


Point::Point(double x, double y, double z) noexcept
    : x(x), y(y), z(z)
{}

Point::Point(double num) noexcept
    : x(num), y(num), z(num)
{}

Point::Point(const Point &other) noexcept
    : x(other.x), y(other.y), z(other.z)
{}

double Point::get_x() const noexcept
{
    return x;
}

double Point::get_y() const noexcept
{
    return y;
}

double Point::get_z() const noexcept
{
    return z;
}

void Point::set_x(double num) noexcept
{
    x = num;
}

void Point::set_y(double num) noexcept
{
    y = num;
}

void Point::set_z(double num) noexcept
{
    z = num;
}

void Point::move(Transformer _transform) noexcept
{
    x += _transform.get_x();
    y += _transform.get_y();
    z += _transform.get_z();
}

void Point::scale(Transformer _transform) noexcept
{
    x *= _transform.get_x();
    y *= _transform.get_y();
    z *= _transform.get_z();
}

void Point::rotate_x(double ax) noexcept
{
    const double radians = ax * M_PI / 180.0;
    const double cosv = cos(radians);
    const double sinv = sin(radians);

    const double tmp = y;

    y = y * cosv - z * sinv;
    z = tmp * sinv + z * cosv;
}

void Point::rotate_y(double ay) noexcept
{
    const double radians = ay * M_PI / 180.0;
    const double cosv = cos(radians);
    const double sinv = sin(radians);

    const double tmp = x;

    x = x * cosv + z * sinv;
    z = tmp * -sinv + z * cosv;
}

void Point::rotate_z(double az) noexcept
{
    const double radians = az * M_PI / 180.0;
    const double cosv = cos(radians);
    const double sinv = sin(radians);

    const double tmp = x;

    x = x * cosv - y * sinv;
    y = tmp * sinv + y * cosv;
}

void Point::rotate(Transformer _transform) noexcept
{
    rotate_z(_transform.get_z());
    rotate_y(_transform.get_y());
    rotate_x(_transform.get_x());
}

void Point::rotate(const Point &center, Transformer _transform) noexcept
{
    move(Transformer(-center.x, -center.y, -center.z));

    rotate_z(_transform.get_z());
    rotate_y(_transform.get_y());
    rotate_x(_transform.get_x());

    move(Transformer(center.x, center.y, center.z));
}

double Point::dotproduct(const Point &other) const
{
    return get_x() * other.get_x() + get_y() * other.get_y() + get_z() * other.get_z();
}

Point Point::crossproduct(const Point &other) const
{
    return Point
    (
        get_y() * other.get_z() - get_z() * other.get_y(),
        get_z() * other.get_x() - get_x() * other.get_z(),
        get_x() * other.get_y() - get_y() * other.get_x()
    );
}

Point Point::normalize() const
{
    double len = std::sqrt(dotproduct(*this));

    if (len < __DBL_EPSILON__)
        return *this;

    return Point
    (
        get_x() / len,
        get_y() / len,
        get_z() / len
    );
}

Point Point::operator-(const Point &other) const
{
    return Point
    (
        get_x() - other.get_x(),
        get_y() - other.get_y(),
        get_z() - other.get_z()
    );
}
