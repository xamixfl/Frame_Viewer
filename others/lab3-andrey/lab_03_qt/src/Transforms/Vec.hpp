//
// Created by nuelex on 21/05/25.
//

#ifndef VEC_HPP
#define VEC_HPP
#include <cmath>

#include "../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Point/Points.hpp"

#define EPS std::numeric_limits<double>::epsilon()

class Vec
{
public:
    Vec() = default;
    Vec(const Vec &) = default;
    Vec(Vec &&) = default;
    explicit Vec(const Point &point) { _x = point.GetX(); _y = point.GetY(); _z = point.GetZ(); }
    Vec(const double& x, const double& y, const double& z) { _x = x, _y = y, _z = z; }
    Vec(const Point& p1, const Point& p2) { _x = p1.GetX() - p2.GetX(); _y = p1.GetY() - p2.GetY(); _z = p1.GetZ() - p2.GetZ(); }

    ~Vec() = default;

    [[nodiscard]] double GetX() const { return _x; }
    [[nodiscard]] double GetY() const { return _y; }
    [[nodiscard]] double GetZ() const { return _z; }

    Vec& operator=(const Vec &) = default;
    Vec& operator=(Vec &&) = default;
    Vec& operator=(const Point &point) { _x = point.GetX(); _y = point.GetY(); _z = point.GetZ(); return *this; }
    Vec& operator=(Point &&point) { _x = point.GetX(); _y = point.GetY(); _z = point.GetZ(); return *this; }

    [[nodiscard]] Vec operator-() const { return {-_x, -_y, -_z}; }

    Vec& operator+=(const Vec &other) { _x += other._x; _y += other._y; _z += other._z; return *this; }
    [[nodiscard]] Vec operator+(const Vec &other) const { Vec tmp(*this); tmp += other; return tmp; }

    Vec& operator-=(const Vec &other) { _x -= other._x; _y -= other._y; _z -= other._z; return *this; }
    [[nodiscard]] Vec operator-(const Vec &other) const { Vec tmp(*this); tmp -= other; return tmp; }

    Vec& operator*=(const Vec &other) { _x *= other._x; _y *= other._y; _z *= other._z; return *this; }
    [[nodiscard]] double operator*(const Vec &other) const { return _x * other._x + _y * other._y + _z * other._z; }

    Vec& operator/=(const double value) { _x /= value; _y /= value; _z /= value; return *this; }
    [[nodiscard]] Vec operator/(const double value) const { Vec tmp(*this); tmp /= value; return tmp; }

    Vec& vecMul(const Vec &other);
    [[nodiscard]] Vec vecMulConst(const Vec &other) const;

    [[nodiscard]] Point toPoint() const { return {_x, _y, _z}; }
    [[nodiscard]] double value() const { return sqrt(_x * _x + _y * _y + _z * _z); }
    void normalize();

private:
    double _x{0};
    double _y{0};
    double _z{0};
};



#endif //VEC_HPP
