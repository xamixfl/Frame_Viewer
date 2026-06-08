#include <QPainter>

#include "drawer.h"

typedef struct {
    QPainter* painter;
} Painter_t;

static void canvas_to_painter(Painter_t* painter, void* canvas) {
    if (!canvas || !painter) return;

    painter->painter = static_cast<QPainter*>(canvas);
}

static void draw_line(Painter_t* painter, double x1, double y1, double x2, double y2) {
    if (!painter) return;

    painter->painter->drawLine(
        QPointF(x1, y1),
        QPointF(x2, y2)
    );
}

static int draw_edge(Painter_t* painter, const ProjectedPoints_t* proj, const Edge_t* edge) {
    if (!painter)
        return RC_ERR_NULL_PTR;
    if (!proj || !edge)
        return RC_ERR_INVALID_ARG;

    int rc = RC_OK;
    Point2D_t start, end;

    rc = projected_get_point(&start, proj, edge_get_start(edge));
    if (rc == RC_OK)
        rc = projected_get_point(&end, proj, edge_get_end(edge));

    if (rc == RC_OK)
        draw_line(painter,
            point2d_get_x(&start), point2d_get_y(&start),
            point2d_get_x(&end), point2d_get_y(&end)
        );

    return rc;
}

static int draw_edges(void* canvas, const ProjectedPoints_t* proj, const EdgeArray_t* edges) {
    if (!canvas)
        return RC_ERR_NULL_PTR;
    if (!proj || !edges)
        return RC_ERR_INVALID_ARG;

    unsigned count = edge_array_get_count(edges);
    int rc = RC_OK;

    Edge_t edge;
    Painter_t painter;
    canvas_to_painter(&painter, canvas);
    for (unsigned i = 0; rc == RC_OK && i < count; i++)
    {
        rc = edge_array_get(&edge, edges, i);
        if (rc == RC_OK)
            rc = draw_edge(&painter, proj, &edge);
    }

    return rc;
}

static int drawer_project_points(ProjectedPoints_t* proj, const Point3DArray_t* points, const DrawSize_t* draw_size) {
    if (!proj)
        return RC_ERR_NULL_PTR;
    if (!points || !draw_size)
        return RC_ERR_INVALID_ARG;

    ProjectionParams_t proj_params = projection_params_init(
        draw_size->width, draw_size->height,
        PROJECTION_DEFAULT_DISTANCE, PROJECTION_SCALE_DIVISOR,
        PROJECTION_CENTER_DIVISOR, PROJECTION_Z_EPSILON
    );

    return projection_project_points(proj, points, &proj_params);
}

int drawer_draw(const DrawRequest_t* draw_data, const Point3DArray_t* points, const EdgeArray_t* edges) {
    if (!points || !edges)
        return RC_ERR_NULL_PTR;
    if (!draw_data || !draw_data->canvas)
        return RC_ERR_INVALID_ARG;

    ProjectedPoints_t proj;
    projected_init(&proj);

    int rc = drawer_project_points(&proj, points, &draw_data->size);
    if (rc == RC_OK)
        rc = draw_edges(draw_data->canvas, &proj, edges);

    projected_free(&proj);

    return rc;
}
