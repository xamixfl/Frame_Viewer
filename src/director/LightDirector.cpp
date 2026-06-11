#include "director/LightDirector.h"
#include "builder/LightBuilder.h"

LightDirector::LightDirector(std::unique_ptr<LightBuilder> builder) noexcept 
    : _builder(std::move(builder)) {}

BaseDirector::ObjectPtr LightDirector::construct(const std::string& config) {
    if (!_builder) return nullptr;

    float x = 0.0f, y = 0.0f, z = 0.0f;
    float r = 1.0f, g = 1.0f, b = 1.0f;
    float intensity = 1.0f;

    if (!config.empty()) {
        x = getParam(config, "x", 0.0f);
        y = getParam(config, "y", 0.0f);
        z = getParam(config, "z", 0.0f);
        r = getParam(config, "r", 1.0f);
        g = getParam(config, "g", 1.0f);
        b = getParam(config, "b", 1.0f);
        intensity = getParam(config, "i", 1.0f);
    }

    _builder->setPosition(Point(x, y, z));
    _builder->setColor(r, g, b);
    _builder->setIntensity(intensity);
    
    _builder->build();

    return _builder->getResult();
}
