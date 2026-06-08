#include <stdlib.h>
#include <math.h>

#include "projection.h"

static int projected_alloc(ProjectedPoints_t* proj, unsigned count) {
    if (!proj)
        return RC_ERR_NULL_PTR;

    int rc = RC_OK;

    if (count == 0) {
        proj->data = NULL;
        proj->count = 0;
    }
    else {
        Point2D_t* data = (Point2D_t*) malloc(sizeof(Point2D_t) * count);
        if (!data)
            rc = RC_ERR_ALLOC;
        else {
            proj->data = data;
            proj->count = count;
        }
    }

    return rc;
}

static double calc_projection_factor(double z, double distance, double z_epsilon) {
    double denom = z + distance;

    if (fabs(denom) < z_epsilon)
        denom = z_epsilon;

    return distance / denom;
}

static double project_coord(double coord, double factor, double scale, double size, double center_divisor) {
    return (coord * factor) * scale + (size / center_divisor);
}

static int project_point(Point2D_t* out, const Point3D_t* in, const ProjectionParams_t* params) {
    if (!out || !in)
        return RC_ERR_NULL_PTR;
    if (!params)
        return RC_ERR_INVALID_ARG;

    double factor = calc_projection_factor(point3d_get_z(in), params->distance, params->z_epsilon);
    double scale = (double)params->width / params->scale_divisor;

    out->x = project_coord(point3d_get_x(in), factor, scale, params->width, params->center_divisor);
    out->y = project_coord(-point3d_get_y(in), factor, scale, params->height, params->center_divisor);

    return RC_OK;
}

ProjectionParams_t projection_params_init(int width, int height, double distance, double scale_divisor, double center_divisor, double z_epsilon) {
    ProjectionParams_t params;

    params.width = width;
    params.height = height;
    params.distance = distance;
    params.scale_divisor = scale_divisor;
    params.center_divisor = center_divisor;
    params.z_epsilon = z_epsilon;

    return params;
}

Point2D_t point2d_init(double x, double y) {
    Point2D_t point;

    point.x = x;
    point.y = y;

    return point;
}

Point2D_t point2d_init_default(void) {
    return point2d_init(0.0, 0.0);
}

double point2d_get_x(const Point2D_t* point) {
    if (!point)
        return 0.0;

    return point->x;
}

double point2d_get_y(const Point2D_t* point) {
    if (!point)
        return 0.0;

    return point->y;
}

void projected_init(ProjectedPoints_t* proj) {
    if (!proj) return;
    if (!projected_is_empty(proj)) return;

    proj->data = NULL;
    proj->count = 0;
}

void projected_free(ProjectedPoints_t* proj) {
    if (!proj) return;

    free(proj->data);
    proj->data = NULL;
    proj->count = 0;
}

int projected_is_empty(const ProjectedPoints_t* proj) {
    if (!proj)
        return 1;

    return (proj->data == NULL || proj->count == 0);
}

int projection_project_points(ProjectedPoints_t* proj, const Point3DArray_t* points, const ProjectionParams_t* params) {
    if (!proj || !points)
        return RC_ERR_NULL_PTR;
    if (!params)
        return RC_ERR_INVALID_ARG;

    unsigned count = point3d_array_get_count(points);

    int rc = projected_alloc(proj, count);

    Point3D_t point;
    Point2D_t projected;
    for (unsigned i = 0; rc == RC_OK && i < count; i++) {
        rc = point3d_array_get(&point, points, i);
        if (rc == RC_OK) {
            rc = project_point(&projected, &point, params);
            if (rc == RC_OK)
                rc = projected_set_point(proj, i, &projected);
        }
    }

    if (rc != RC_OK)
        projected_free(proj);

    return rc;
}

int projected_get_point(Point2D_t* point, const ProjectedPoints_t* proj, unsigned index) {
    if (!point || !proj || !proj->data)
        return RC_ERR_NULL_PTR;
    if (index >= proj->count)
        return RC_ERR_OUT_OF_RANGE;

    *point = proj->data[index];

    return RC_OK;
}

int projected_set_point(ProjectedPoints_t* proj, unsigned index, const Point2D_t* point) {
    if (!proj || !proj->data || !point)
        return RC_ERR_NULL_PTR;
    if (index >= proj->count)
        return RC_ERR_OUT_OF_RANGE;

    proj->data[index] = *point;

    return RC_OK;
}
