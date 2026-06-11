#include "builder/LightBuilder.h"
#include "bridge/LightImpl.h"
#include "composite/Light.h"

LightBuilder::LightBuilder(std::unique_ptr<BaseReader> reader) noexcept 
    : BaseBuilder(std::move(reader)) 
{
    _initLight();
}

LightBuilder::~LightBuilder() = default;

void LightBuilder::build() {}

void LightBuilder::setPosition(const Point& pos) {
    if (_lightImpl) {
        _lightImpl->setPosition(pos);
    }
}

void LightBuilder::setColor(float r, float g, float b) {
    if (_lightImpl) {
        _lightImpl->setColor(r, g, b);
    }
}

void LightBuilder::setIntensity(float intensity) {
    if (_lightImpl) {
        _lightImpl->setIntensity(intensity);
    }
}

std::shared_ptr<BaseObject> LightBuilder::getResult() {
    return std::make_shared<Light>(std::move(_lightImpl));
}

void LightBuilder::_initLight() noexcept {
    _lightImpl = std::make_unique<LightImpl>();
}
