#ifndef TRIANGLECARCAS_H
#define TRIANGLECARCAS_H

#include <vector>
#include <cmath>
#include "AbstractCarcas.h"
#include "Carcas.h"

class TriangleCarcas : public AbstractCarcas
{
public:
    using Triangle = std::array<int,3>;

    TriangleCarcas() = default;
    TriangleCarcas(std::vector<Point>& points, const std::vector<Triangle>& links);

    std::vector<Point>& get_points() override;

    std::vector<Link> get_links() override {
        return {};
    }

    std::vector<Triangle> getTriangles() override {
        return indices;
    }

    bool add_point(const Point& point) override;

    bool add_link(const Link& link) override {
        return false;
    }

    Point& get_center() override;
    void move_to_center() override;
    void move_back() override;

protected:
    std::vector<Point> points;
    std::vector<Triangle> indices;
    Point center;

private:
    void revalue_center();
};

#endif // TRIANGLECARCAS_H
