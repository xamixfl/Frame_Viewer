#include "LightImpl.h"
#include <algorithm>
#include <cmath>

extern double dot(const Point& a, const Point& b);
extern Point sub(const Point& a, const Point& b);
extern Point normalize(const Point& a);

void LightImpl::getIntensityAt(const Point& point, const Point& normal, 
                               float& r, float& g, float& b) const noexcept {
    Point lPos = getPosition();
    Point L = normalize(sub(lPos, point));

    float dotNL = std::max(0.0, dot(normal, L));
    float lr, lg, lb;
    getColor(lr, lg, lb);
    float i = getIntensity();
    
    r = lr * dotNL * i;
    g = lg * dotNL * i;
    b = lb * dotNL * i;
}
