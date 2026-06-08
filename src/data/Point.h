#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point() noexcept : _x(0.0), _y(0.0), _z(0.0) {}
    Point(double x_, double y_, double z_) noexcept : _x(x_), _y(y_), _z(z_) {}

    [[nodiscard]] double getX() const noexcept { return _x; }
    [[nodiscard]] double getY() const noexcept { return _y; }
    [[nodiscard]] double getZ() const noexcept { return _z; }

    void setX(double v) noexcept { _x = v; }
    void setY(double v) noexcept { _y = v; }
    void setZ(double v) noexcept { _z = v; }

    void move(double dx, double dy, double dz) noexcept;
    void rotate(double ax, double ay, double az) noexcept;
    void scale(double sx, double sy, double sz) noexcept;

private:
    double _x;
    double _y;
    double _z;
};

#endif // POINT_H
