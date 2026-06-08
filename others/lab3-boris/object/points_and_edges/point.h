#ifndef POINT_H__
#define POINT_H__

#include "transformer.h"


class Point
{
public:
    Point() noexcept = default;
    Point(double x, double y, double z) noexcept;

    explicit Point(double num) noexcept;
    Point(const Point &other) noexcept;

    double get_x() const noexcept;
    double get_y() const noexcept;
    double get_z() const noexcept;

    void set_x(double num) noexcept;
    void set_y(double num) noexcept;
    void set_z(double num) noexcept;

    void move(Transformer _transform) noexcept;
    void scale(Transformer _transform) noexcept;
    void rotate(Transformer _transform) noexcept;
    void rotate(const Point &center, Transformer _transform) noexcept;

    double dotproduct(const Point &other) const;
    Point crossproduct(const Point &other) const;
    Point normalize() const;
    Point operator-(const Point &other) const;
    Point& operator=(const Point&) noexcept = default;

private:
    double x, y, z;

    void rotate_x(double ax) noexcept;
    void rotate_y(double ay) noexcept;
    void rotate_z(double az) noexcept;
};

#endif
