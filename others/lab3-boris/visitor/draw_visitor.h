#ifndef DRAW_VISITOR_H__
#define DRAW_VISITOR_H__

#include <memory>
#include "base_visitor.h"
#include "drawer_facory.h"
#include  "camera.h"
#include "model.h"


class DrawVisitor : public BaseVisitor
{
public:
    DrawVisitor() = default;
    explicit DrawVisitor(std::shared_ptr<DrawerFactory> fact, std::shared_ptr<Camera> cam, int _width, int _height);
    ~DrawVisitor() override = default;

    void visit(ModelImpl &obj) override;
    void visit(CameraImpl &obj) override;

private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<DrawerFactory> factory;
    int width;
    int height;

    Point get_proection(const Point &point);
};

#endif
