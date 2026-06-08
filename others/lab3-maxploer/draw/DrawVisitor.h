#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include <memory>
#include <cmath>
#include <iostream>
#include "AbstractGraphicFactory.h"
#include "../visitor/AbstractVisitor.h"

class DrawVisitor : public AbstractVisitor
{
public:
    DrawVisitor();
    DrawVisitor(const DrawVisitor& visitor) = default;
    ~DrawVisitor() = default;

    void set_camera(std::shared_ptr<Camera> camera) { this->camera = camera; }
    Point toCameraSpace(const Point& W);

protected:
    std::shared_ptr<AbstractGraphicFactory> factory;
    std::shared_ptr<Camera> camera;

    Point get_proection(const Point& point);
};

#endif // DRAWVISITOR_H
