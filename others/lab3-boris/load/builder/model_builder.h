#ifndef MODEL_BUILDER_H__
#define MODEL_BUILDER_H__

#include "builder.h"
#include "point.h"
#include "edge.h"
#include "object.h"
#include "model.h"


class WireframeModelBuilder : public Builder
{
public:
    WireframeModelBuilder() = default;
    explicit WireframeModelBuilder(std::shared_ptr<Loader> _loader);
    ~WireframeModelBuilder() override;

    void build() override;
    std::shared_ptr<Object> get_result() override;

private:
    std::vector<Point> points;
    std::vector<Edge> edges;
    std::vector<Face> faces;

    void create_points();
    void create_edges();
    void create_faces();
};


class AdjMatrixModelBuilder : public Builder
{
public:
    AdjMatrixModelBuilder() = default;
    explicit AdjMatrixModelBuilder(std::shared_ptr<Loader> _loader);
    ~AdjMatrixModelBuilder() override;

    void build() override;
    std::shared_ptr<Object> get_result() override;

private:
    std::vector<Point> points;
    std::vector<std::vector<bool>> adj;
    std::vector<Face> faces;

    void create_points();
    void create_adj();
    void create_faces();
};

#endif
