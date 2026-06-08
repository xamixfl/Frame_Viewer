#ifndef LIGHTIMPL_H
#define LIGHTIMPL_H

#include "bridge/BaseLightImpl.h"

class LightImpl final : public BaseLightImpl {
public:
    LightImpl() noexcept : _r(1.0f), _g(1.0f), _b(1.0f), _intensity(1.0f), _pos(0,0,0) {}

    void setColor(float r, float g, float b) noexcept override { _r = r; _g = g; _b = b; }
    void setIntensity(float i) noexcept override { _intensity = i; }
    void getColor(float& r, float& g, float& b) const noexcept override { r = _r; g = _g; b = _b; }
    virtual void getIntensityAt(const Point& point, const Point& normal, 
                            float& r, float& g, float& b) const noexcept = 0;

    // Реализация новых методов
    void setPosition(const Point& pos) noexcept override { _pos = pos; }
    Point getPosition() const noexcept override { return _pos; }

private:
    float _r, _g, _b;
    float _intensity;
    Point _pos; // Добавлено поле позиции
};

#endif
