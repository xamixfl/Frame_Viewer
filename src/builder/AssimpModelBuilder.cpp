#include "builder/AssimpModelBuilder.h"
#include "bridge/AssimpModelImpl.h"
#include "composite/Model.h" 
#include "director/AssimpDirector.h"

AssimpModelBuilder::~AssimpModelBuilder() = default;

AssimpModelBuilder::AssimpModelBuilder(std::unique_ptr<BaseReader> reader) 
    : BaseBuilder(std::move(reader)) 
{
    _initModel();
}

void AssimpModelBuilder::addPoint(const Point& p) {
    if (_model) {
        _model->addPoint(p);
    }
}

void AssimpModelBuilder::addFace(const Face& f) {
    if (_model) {
        _model->addFace(f);
    }
}

void AssimpModelBuilder::setMaterial(const Material& m) {
    if (_model) {
        _model->setMaterial(m);
    }
}

std::shared_ptr<BaseObject> AssimpModelBuilder::getResult() {
    return std::make_shared<Model>(std::move(_model));
}

void AssimpModelBuilder::_initModel() noexcept {
    _model = std::make_unique<AssimpModelImpl>();
}

// Пустой build(), так как сборкой управляет Director
void AssimpModelBuilder::build() {}
