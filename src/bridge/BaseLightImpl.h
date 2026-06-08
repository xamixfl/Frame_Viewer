#ifndef BASELIGHTIMPL_H
#define BASELIGHTIMPL_H

#include "../data/Point.h"

class BaseLightImpl {
public:
    virtual ~BaseLightImpl() = default;

    virtual void setColor(float r, float g, float b) noexcept = 0;
    virtual void setIntensity(float i) noexcept = 0;
    virtual void getColor(float& r, float& g, float& b) const noexcept = 0;
    virtual float getIntensity() const noexcept = 0;
    virtual void setPosition(const Point& pos) noexcept = 0;
    virtual Point getPosition() const noexcept = 0;

    virtual void getIntensityAt(const Point& point, const Point& normal, 
                                float& r, float& g, float& b) const noexcept = 0;
};

#endif
