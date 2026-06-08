#include "data/Point.h"
#include <cmath>

void Point::move(double dx, double dy, double dz) noexcept {
    _x += dx;
    _y += dy;
    _z += dz;
}

void Point::normalizeNormal() noexcept {
    double len = std::sqrt(_nx * _nx + _ny * _ny + _nz * _nz);
    if (len > 1e-9) {
        _nx /= len; _ny /= len; _nz /= len;
    }
}

void Point::rotate(double ax, double ay, double az) noexcept {
    auto rotateVec = [&](double& x, double& y, double& z) {
        double sinX = std::sin(ax), cosX = std::cos(ax);
        double y1 = y * cosX - z * sinX;
        double z1 = y * sinX + z * cosX;
        y = y1; z = z1;

        double sinY = std::sin(ay), cosY = std::cos(ay);
        double x2 = x * cosY + z * sinY;
        double z2 = -x * sinY + z * cosY;
        x = x2; z = z2;

        double sinZ = std::sin(az), cosZ = std::cos(az);
        double x3 = x * cosZ - y * sinZ;
        double y3 = x * sinZ + y * cosZ;
        x = x3; y = y3;
    };

    rotateVec(_x, _y, _z);
    rotateVec(_nx, _ny, _nz);
}

void Point::scale(double sx, double sy, double sz) noexcept {
    _x *= sx;
    _y *= sy;
    _z *= sz;

    if (std::abs(sx) > 1e-9) _nx /= sx;
    if (std::abs(sy) > 1e-9) _ny /= sy;
    if (std::abs(sz) > 1e-9) _nz /= sz;
    normalizeNormal();
}
