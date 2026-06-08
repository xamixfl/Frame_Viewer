#include "transform_visitor.h"
#include "model.h"
#include "camera.h"


MoveVisitor::MoveVisitor(Transformer _transform)
{
    transform = std::move(_transform);
}

ScaleVisitor::ScaleVisitor(Transformer _transform)
{
    transform = std::move(_transform);
}

RotateVisitor::RotateVisitor(Transformer _transform)
{
    transform = std::move(_transform);
}


void MoveVisitor::visit(ModelImpl &obj)
{
    for (auto &point : obj.get_points())
    {
        point.move(transform);
    }

    obj.get_center().move(transform);
}

void MoveVisitor::visit(CameraImpl &obj)
{
    Point pos = obj.get_position();
    pos.move(transform);
    obj.set_position(pos);

    Point tar = obj.get_target();
    tar.move(transform);
    obj.set_target(tar);
}


void ScaleVisitor::visit(ModelImpl &obj)
{
    obj.move_to_center();

    for (auto &point : obj.get_points())
    {
        point.scale(transform);
    }

    obj.move_back();
}

void ScaleVisitor::visit(CameraImpl &obj)
{
    Point pos = obj.get_position();
    Point tar = obj.get_target();

    pos.move(Transformer(-tar.get_x(), -tar.get_y(), -tar.get_z()));
    pos.scale(transform);
    pos.move(Transformer(tar.get_x(), tar.get_y(), tar.get_z()));

    obj.set_position(pos);
}


void RotateVisitor::visit(ModelImpl &obj)
{
    obj.move_to_center();

    for (auto &point : obj.get_points())
    {
        point.rotate(transform);
    }

    obj.move_back();
}

void RotateVisitor::visit(CameraImpl &obj)
{
    Point pos = obj.get_position();
    Point tar = obj.get_target();

    pos.rotate(tar, transform);

    obj.set_position(pos);

    Point _up = obj.get_up();
    Point origin(0, 0, 0);
    _up.rotate(origin, transform);
    obj.set_up(_up);
}
