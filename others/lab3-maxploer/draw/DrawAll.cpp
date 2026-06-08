#include "DrawAll.h"

DrawAll::DrawAll() {}

DrawAll::DrawAll(std::shared_ptr<AbstractGraphicFactory> factory, std::shared_ptr<Camera>  camera)
{
    this->factory = factory;
    this->camera = camera;
}

DrawAll::DrawAll(const DrawAll& visitor)
{
    this->camera = visitor.camera;
    this->factory = visitor.factory;
}

void DrawAll::visit(Model& carcas)
{
    auto points = carcas.model->get_points();
    auto links = carcas.model->get_links();
    auto drawer = this->factory->get_drawer();

    if (links.empty())
    {
        auto triangles = carcas.model->getTriangles();
        for (auto& triangle: triangles)
        {
            Point& w0 = points[triangle[0]];
            Point& w1 = points[triangle[1]];
            Point& w2 = points[triangle[2]];

            Point c0 = toCameraSpace(w0);
            Point c1 = toCameraSpace(w1);
            Point c2 = toCameraSpace(w2);

            Point e1 = c2 - c0;
            Point e2 = c1 - c0;
            Point normal = e1.cross(e2);

            if (normal.get_z() >= 0)
                continue;
            
            Point p0 = get_proection(w0);
            Point p1 = get_proection(w1);
            Point p2 = get_proection(w2);

            drawer->draw_line(p0, p1);
            drawer->draw_line(p1, p2);
            drawer->draw_line(p2, p0);
        }
    }
    for (auto& link : links)
    {
        Point left = this->get_proection(points[link.get_left()]);
        Point right = this->get_proection(points[link.get_right()]);

        if (left.get_z() < -1 || right.get_z() < -1)
            continue;
        if (left.get_z() > 1 || right.get_z() > 1)
            continue;
        else if (left.get_z() > 0 && right.get_z() > 0)
            drawer->draw_line(left, right);
    }
}

void DrawAll::visit(Camera& camera)
{
    return;
}

void DrawAll::visit(CompositeObject& obj)
{
    obj.accept(std::make_shared<DrawAll>(*this));
}
