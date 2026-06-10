#ifndef TRANSFORM_H
#define TRANSFORM_H

class Transform final {
public:
    Transform() noexcept : _x(0.0), _y(0.0), _z(0.0) {}
    Transform(double x, double y, double z) noexcept : _x(x), _y(y), _z(z) {}

    [[nodiscard]] double getX() const noexcept { return _x; }
    [[nodiscard]] double getY() const noexcept { return _y; }
    [[nodiscard]] double getZ() const noexcept { return _z; }

private:
    double _x;
    double _y;
    double _z;
};

#endif 
