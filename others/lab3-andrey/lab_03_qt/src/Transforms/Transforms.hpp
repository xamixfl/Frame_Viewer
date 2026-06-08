//
// Created by nuelex on 09/05/25.
//

#ifndef TRANSFORMS_HPP
#define TRANSFORMS_HPP

#include "../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Point/Points.hpp"

class BaseTransform
{
public:
    virtual ~BaseTransform() = default;
};

class Mover : public BaseTransform
{
public:
    Mover() = default;
    Mover(const Mover &) = default;
    explicit Mover(const Point &point) { this->setDx(point.GetX()); this->setDy(point.GetY()); this->setDz(point.GetZ()); }
    Mover(const double dx_, const double dy_, const double dz_, const Point &center_) : dx(dx_), dy(dy_), dz(dz_), center(center_) {}
    ~Mover() override = default;

    Mover &operator=(const Mover &) = default;
    Mover operator -();

    [[nodiscard]] double getDx() const noexcept { return dx; }
    [[nodiscard]] double getDy() const noexcept { return dy; }
    [[nodiscard]] double getDz() const noexcept { return dz; }

    void setDx(const double dx_) { dx = dx_; }
    void setDy(const double dy_) { dy = dy_; }
    void setDz(const double dz_) { dz = dz_; }
    void setCenter(const Point &center_) { center = center_; }

private:
    double dx{0};
    double dy{0};
    double dz{0};
    Point center{};
};

class Rotater : public BaseTransform
{
public:
    Rotater() = default;
    explicit Rotater(const Rotater &) = default;
    Rotater(const double ox_, const double oy_, const double oz_, const Point &center_) : ox(ox_), oy(oy_), oz(oz_), center(center_) {}
    ~Rotater() override = default;

    Rotater &operator=(const Rotater &) = default;

    [[nodiscard]] double getOx() const noexcept { return ox; }
    [[nodiscard]] double getOy() const noexcept { return oy; }
    [[nodiscard]] double getOz() const noexcept { return oz; }
    [[nodiscard]] const Point &getCenter() const noexcept { return center; }

    void setOx(const double ox_) { ox = ox_; }
    void setOy(const double oy_) { oy = oy_; }
    void setOz(const double oz_) { oz = oz_; }
    void setCenter(const Point &center_) { center = center_; }

    [[nodiscard]] Mover centerToMover() const;

private:
    double ox{0};
    double oy{0};
    double oz{0};
    Point center{};
};

class Scaler : public BaseTransform
{
public:
    Scaler() = default;
    explicit Scaler(const Scaler &) = default;
    Scaler(const double kx_, const double ky_, const double kz_, const Point &center_) : kx(kx_), ky(ky_), kz(kz_), center(center_) {}
    ~Scaler() override = default;

    Scaler &operator=(const Scaler &) = default;

    [[nodiscard]] double getKx() const noexcept { return kx; }
    [[nodiscard]] double getKy() const noexcept { return ky; }
    [[nodiscard]] double getKz() const noexcept { return kz; }
    [[nodiscard]] const Point &getCenter() const noexcept { return center; }

    void setKx(const double kx_) { kx = kx_; }
    void setKy(const double ky_) { ky = ky_; }
    void setKz(const double kz_) { kz = kz_; }
    void setCenter(const Point &center_) { center = center_; }

    [[nodiscard]] Mover centerToMover() const;

private:
    double kx{0};
    double ky{0};
    double kz{0};
    Point center{};
};

#endif //TRANSFORMS_HPP
