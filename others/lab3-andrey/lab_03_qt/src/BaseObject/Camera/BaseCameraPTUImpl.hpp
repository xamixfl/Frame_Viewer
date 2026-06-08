//
// Created by nuelex on 25/05/25.
//

#ifndef BASECAMERAPTUIMPL_HPP
#define BASECAMERAPTUIMPL_HPP
#include "../../Transforms/Transforms.hpp"
#include "../../Transforms/Vec.hpp"


class BaseCameraPTUImpl
{
public:
    BaseCameraPTUImpl() = default;
    virtual ~BaseCameraPTUImpl() = default;

    [[nodiscard]] virtual const Point &getPosition() const = 0;
    virtual void setPosition(const Point &position) = 0;
    virtual void setPosition(Point&& position) = 0;

    [[nodiscard]] virtual const Point &getTarget() const = 0;
    virtual void setTarget(const Point &target) = 0;
    virtual void setTarget(Point &&target) = 0;

    [[nodiscard]] virtual const Vec &getUp() const = 0;
    virtual void setUp(const Point &up) = 0;
    virtual void setUp(Point &&up) = 0;
    virtual void setUp(const Vec &up) = 0;
    virtual void setUp(Vec &&up) = 0;

    virtual void transform(const Mover &mover) = 0;
    virtual void transform(const Rotater &rotater) = 0;
};



#endif //BASECAMERAPTUIMPL_HPP
