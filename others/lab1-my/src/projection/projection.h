#ifndef PROJECTION_H
#define PROJECTION_H

#include "common_types.h"
#include "point.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double x, y;
} Point2D_t;

typedef struct {
    Point2D_t* data;
    unsigned count;
} ProjectedPoints_t;

typedef struct {
    int width;
    int height;
    double distance;
    double scale_divisor;
    double center_divisor;
    double z_epsilon;
} ProjectionParams_t;

ProjectionParams_t projection_params_init(int width, int height, double distance, double scale_divisor, double center_divisor, double z_epsilon);

Point2D_t point2d_init(double x, double y);

Point2D_t point2d_init_default(void);

double point2d_get_x(const Point2D_t* point);

double point2d_get_y(const Point2D_t* point);

void projected_init(ProjectedPoints_t* proj);

void projected_free(ProjectedPoints_t* proj);

int projected_is_empty(const ProjectedPoints_t* proj);

int projection_project_points(ProjectedPoints_t* proj, const Point3DArray_t* points, const ProjectionParams_t* params);

int projected_get_point(Point2D_t* point, const ProjectedPoints_t* proj, unsigned index);

int projected_set_point(ProjectedPoints_t* proj, unsigned index, const Point2D_t* point);

#ifdef __cplusplus
}
#endif

#endif // PROJECTION_H
