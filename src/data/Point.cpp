#include "data/Point.h"
#include <cmath>

void Point::move(double dx, double dy, double dz) noexcept {
    _x += dx;
    _y += dy;
    _z += dz;
}

void Point::rotate(double ax, double ay, double az) noexcept {
    double sinX = std::sin(ax), cosX = std::cos(ax);
    double sinY = std::sin(ay), cosY = std::cos(ay);
    double sinZ = std::sin(az), cosZ = std::cos(az);

    double y1 = _y * cosX - _z * sinX;
    double z1 = _y * sinX + _z * cosX;
    _y = y1;
    _z = z1;

    double x2 = _x * cosY + _z * sinY;
    double z2 = -_x * sinY + _z * cosY;
    _x = x2;
    _z = z2;

    double x3 = _x * cosZ - _y * sinZ;
    double y3 = _x * sinZ + _y * cosZ;
    _x = x3;
    _y = y3;
}

void Point::scale(double sx, double sy, double sz) noexcept {
    _x *= sx;
    _y *= sy;
    _z *= sz;
}
