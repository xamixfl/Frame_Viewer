#include "LightImpl.h"
#include "data/Point.h"
#include <algorithm>
#include <cmath>
#include <cstdio>

void LightImpl::getIntensityAt(const Point& point, const Point& normal, 
                               float& r, float& g, float& b) const noexcept {
    Point lPos = getPosition();
    Point L = normalize(sub(lPos, point));

    float dotNL = std::abs(dot(normal, L)); 
    float lr, lg, lb;
    getColor(lr, lg, lb);
    float i = getIntensity();
    
    r = lr * dotNL * i;
    g = lg * dotNL * i;
    b = lb * dotNL * i;
}

float LightImpl::getIntensity() const noexcept {
    return _intensity;
}
