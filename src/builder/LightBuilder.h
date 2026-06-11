#ifndef LIGHTBUILDER_H
#define LIGHTBUILDER_H

#include "builder/BaseBuilder.h"
#include "composite/BaseObject.h"
#include "data/Point.h"

class LightImpl;

class LightBuilder : public BaseBuilder {
public:
    explicit LightBuilder(std::unique_ptr<BaseReader> reader = nullptr) noexcept;
    ~LightBuilder() override;

    void build() override;

    void setPosition(const Point& pos);
    void setColor(float r, float g, float b);
    void setIntensity(float intensity);

    std::shared_ptr<BaseObject> getResult();

private:
    std::unique_ptr<LightImpl> _lightImpl;
    void _initLight() noexcept;
};

#endif // LIGHTBUILDER_H
