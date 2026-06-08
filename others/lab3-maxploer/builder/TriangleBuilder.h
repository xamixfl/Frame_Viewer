#ifndef TRIANGLEBUILDER_H
#define TRIANGLEBUILDER_H

#include "BaseCarcasBuilder.h"
#include "../object/carcas/Carcas.h"
#include "../object/carcas/TriangleCarcas.h"

class TriangleBuilder : public BaseCarcasBuilder
{
public:
    using Triangle = std::array<int,3>;

    TriangleBuilder() = default;
    explicit TriangleBuilder(std::shared_ptr<AbstractReader> reader);
    ~TriangleBuilder();

    bool build_points() override;
    bool build_links() override;

    void create_model() override;
    std::shared_ptr<Model> build() override;

private:
    std::vector<Point> points;
    std::vector<Triangle> indices;
    int stage = 0;
};

#endif // TRIANGLEBUILDER_H
