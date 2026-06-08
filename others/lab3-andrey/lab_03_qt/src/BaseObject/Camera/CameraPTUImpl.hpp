//
// Created by nuelex on 25/05/25.
//

#ifndef CAMERAPTUIMPL_HPP
#define CAMERAPTUIMPL_HPP
#include "BaseCameraPTUImpl.hpp"
#include "Camera.hpp"
#include "../../Transforms/Transforms.hpp"
#include "../../Transforms/Vec.hpp"


class CameraPTUImpl : public BaseCameraPTUImpl
{
public:
    CameraPTUImpl() = default;
    ~CameraPTUImpl() override = default;

    [[nodiscard]] const Point &getPosition() const override { return _position; }
    void setPosition(const Point &position) override  { _position = position; }
    void setPosition(Point&& position) override  { _position = position; }

    [[nodiscard]] const Point &getTarget() const override  { return _target; }
    void setTarget(const Point &target) override  { _target = target; }
    void setTarget(Point &&target) override  { _target = target; }

    [[nodiscard]] const Vec &getUp() const override  { return _up; }
    void setUp(const Point &up) override  { _up = up; }
    void setUp(Point &&up) override  { _up = up; }
    void setUp(const Vec &up) override  { _up = up; }
    void setUp(Vec &&up) override  { _up = up; }

    void transform(const Mover &mover) override;
    void transform(const Rotater &rotater) override;

private:
    Point _position;
    Point _target;
    Vec _up;

    static Rotater radFromDegree(const Rotater &rotater);
};



#endif //CAMERAPTUIMPL_HPP
