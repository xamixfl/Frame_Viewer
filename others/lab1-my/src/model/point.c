#include <stdlib.h>
#include <string.h>

#include "point.h"

typedef struct {
    double c1;
    double c2;
} CoordPair_t;

static int get_rotation_coords(double** coord1, double** coord2, Point3D_t* point, Axis_t axis) {
    if (!coord1 || !coord2 || !point)
        return RC_ERR_NULL_PTR;

    int rc = RC_OK;

    switch (axis) {
        case AXIS_X:
            *coord1 = &point->y;
            *coord2 = &point->z;
            break;
        case AXIS_Y:
            *coord1 = &point->x;
            *coord2 = &point->z;
            break;
        case AXIS_Z:
            *coord1 = &point->x;
            *coord2 = &point->y;
            break;
        default:
            rc = RC_ERR_INVALID_ARG;
            break;
    }

    return rc;
}

static int rotate_pair(double* a, double* b, double angle) {
    if (!a || !b)
        return RC_ERR_NULL_PTR;

    double cos_a = cos(angle);
    double sin_a = sin(angle);

    double old_a = *a;
    double old_b = *b;

    *a = old_a * cos_a - old_b * sin_a;
    *b = old_a * sin_a + old_b * cos_a;

    return RC_OK;
}

static int shift_coords(double* c1, double* c2, double center1, double center2, double sign) {
    if (!c1 || !c2)
        return RC_ERR_NULL_PTR;

    *c1 += sign * center1;
    *c2 += sign * center2;

    return RC_OK;
}

static int get_center_coords(CoordPair_t* pair, const Point3D_t* center, Axis_t axis) {
    if (!pair)
        return RC_ERR_NULL_PTR;
    if (!center)
        return RC_ERR_INVALID_ARG;

    Point3D_t tmp = *center;
    double* p1 = NULL;
    double* p2 = NULL;

    int rc = get_rotation_coords(&p1, &p2, &tmp, axis);

    if (rc == RC_OK) {
        pair->c1 = *p1;
        pair->c2 = *p2;
    }

    return rc;
}

static int point3d_add(Point3D_t* result, const Point3D_t* a, const Point3D_t* b) {
    if (!result)
        return RC_ERR_NULL_PTR;
    if (!a || !b)
        return RC_ERR_INVALID_ARG;

    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;

    return RC_OK;
}

static int point3d_array_sum(Point3D_t* sum, const Point3DArray_t* arr) {
    if (!sum)
        return RC_ERR_NULL_PTR;
    if (!arr)
        return RC_ERR_INVALID_ARG;

    *sum = point3d_init_default();
    int rc = RC_OK;
    unsigned count = point3d_array_get_count(arr);

    for (unsigned i = 0; rc == RC_OK && i < count; i++) {
        Point3D_t point;
        rc = point3d_array_get(&point, arr, i);
        if (rc == RC_OK)
            rc = point3d_add(sum, sum, &point);
    }

    return rc;
}

static int apply_rotation(Point3DArray_t* arr, const RotationParams_t* params) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!params)
        return RC_ERR_INVALID_ARG;

    int rc = RC_OK;
    unsigned count = point3d_array_get_count(arr);

    for (unsigned i = 0; rc == RC_OK && i < count; ++i) {
        Point3D_t point;
        rc = point3d_array_get(&point, arr, i);
        if (rc == RC_OK)
            rc = point3d_rotate(&point, params);
        if (rc == RC_OK)
            rc = point3d_array_set(arr->data, i, &point);
    }

    return rc;
}

Point3D_t point3d_init(double x, double y, double z) {
    Point3D_t point;

    point.x = x;
    point.y = y;
    point.z = z;

    return point;
}

Point3D_t point3d_init_default(void) {
    return point3d_init(0, 0, 0);
}

Point3D_t point3d_init_axis(double value, Axis_t axis) {
    Point3D_t point = point3d_init_default();

    if (axis == AXIS_X) point.x = value;
    else if (axis == AXIS_Y) point.y = value;
    else if (axis == AXIS_Z) point.z = value;

    return point;
}

double point3d_get_x(const Point3D_t* point) {
    if (!point)
        return 0.0;

    return point->x;
}

double point3d_get_y(const Point3D_t* point) {
    if (!point)
        return 0.0;

    return point->y;
}

double point3d_get_z(const Point3D_t* point) {
    if (!point)
        return 0.0;

    return point->z;
}

RotationParams_t rotation_params_init(const Point3D_t* center, double angle, Axis_t axis) {
    RotationParams_t params;

    params.center = *center;
    params.angle = angle;
    params.axis = axis;

    return params;
}

int point3d_move(Point3D_t* point, const Point3D_t* delta) {
    if (!point)
        return RC_ERR_NULL_PTR;
    if (!delta)
        return RC_ERR_INVALID_ARG;

    point->x += delta->x;
    point->y += delta->y;
    point->z += delta->z;

    return RC_OK;
}

int point3d_scale(Point3D_t* point, double factor) {
    if (!point)
        return RC_ERR_NULL_PTR;

    point->x *= factor;
    point->y *= factor;
    point->z *= factor;

    return RC_OK;
}

int point3d_rotate(Point3D_t* point, const RotationParams_t* params) {
    if (!point)
        return RC_ERR_NULL_PTR;
    if (!params)
        return RC_ERR_INVALID_ARG;

    double* coord1 = NULL;
    double* coord2 = NULL;
    int rc = get_rotation_coords(&coord1, &coord2, point, params->axis);

    CoordPair_t center;
    if (rc == RC_OK)
        rc = get_center_coords(&center, &params->center, params->axis);

    if (rc == RC_OK)
        rc = shift_coords(coord1, coord2, center.c1, center.c2, -1.0);
    if (rc == RC_OK)
        rc = rotate_pair(coord1, coord2, params->angle);
    if (rc == RC_OK)
        rc = shift_coords(coord1, coord2, center.c1, center.c2, 1.0);

    return rc;
}

void point3d_array_init(Point3DArray_t* arr) {
    if (!arr) return;
    if (!point3d_array_is_empty(arr)) return;

    arr->data = NULL;
    arr->count = 0;
}

int point3d_array_alloc(Point3DArray_t* arr, unsigned count) {
    if (!arr)
        return RC_ERR_NULL_PTR;

    int rc = RC_OK;

    if (count == 0) {
        arr->data = NULL;
        arr->count = count;
    }
    else {
        Point3D_t* data = (Point3D_t*) malloc(sizeof(Point3D_t) * count);
        if (!data)
            rc = RC_ERR_ALLOC;
        else {
            arr->data = data;
            arr->count = count;
        }
    }

    return rc;
}

void point3d_array_free(Point3DArray_t* arr) {
    if (!arr) return;

    free(arr->data);
    arr->data = NULL;
    arr->count = 0;
}

int point3d_array_copy(Point3DArray_t* dst, const Point3DArray_t* src) {
    if (!dst)
        return RC_ERR_NULL_PTR;
    if (!src)
        return RC_ERR_INVALID_ARG;

    int rc = point3d_array_alloc(dst, src->count);

    if (rc == RC_OK && src->count > 0)
        memcpy(dst->data, src->data, sizeof(Point3D_t) * src->count);

    return rc;
}

void point3d_array_swap(Point3DArray_t* a, Point3DArray_t* b) {
    if (!a || !b) return;

    Point3DArray_t tmp = *a;
    *a = *b;
    *b = tmp;
}

unsigned point3d_array_get_count(const Point3DArray_t* arr) {
    if (!arr)
        return 0;

    return arr->count;
}

int point3d_array_is_empty(const Point3DArray_t* arr) {
    if (!arr)
        return 1;

    return (arr->data == NULL || arr->count == 0);
}

int point3d_array_get(Point3D_t* point, const Point3DArray_t* arr, unsigned index) {
    if (!point)
        return RC_ERR_NULL_PTR;
    if (!arr)
        return RC_ERR_INVALID_ARG;
    if (index >= arr->count)
        return RC_ERR_OUT_OF_RANGE;

    *point = arr->data[index];

    return RC_OK;
}

int point3d_array_set(Point3D_t* arr, unsigned index, const Point3D_t* point) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!point)
        return RC_ERR_INVALID_ARG;

    arr[index] = *point;

    return RC_OK;
}

int point3d_array_move(Point3DArray_t* arr, const Point3D_t* delta) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!delta)
        return RC_ERR_INVALID_ARG;
    if (point3d_array_is_empty(arr))
        return RC_ERR_EMPTY_DATA;

    int rc = RC_OK;
    unsigned count = point3d_array_get_count(arr);

    Point3D_t point;
    for (unsigned i = 0; rc == RC_OK && i < count; ++i) {
        rc = point3d_array_get(&point, arr, i);
        if (rc == RC_OK)
            rc = point3d_move(&point, delta);
        if (rc == RC_OK)
            rc = point3d_array_set(arr->data, i, &point);
    }

    return rc;
}

int point3d_array_scale(Point3DArray_t* arr, double factor) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (point3d_array_is_empty(arr))
        return RC_ERR_EMPTY_DATA;

    int rc = RC_OK;
    unsigned count = point3d_array_get_count(arr);

    for (unsigned i = 0; rc == RC_OK && i < count; ++i) {
        Point3D_t point;
        rc = point3d_array_get(&point, arr, i);
        if (rc == RC_OK)
            rc = point3d_scale(&point, factor);
        if (rc == RC_OK)
            rc = point3d_array_set(arr->data, i, &point);
    }

    return rc;
}

int point3d_array_calc_center(Point3D_t* center, const Point3DArray_t* arr) {
    if (!center)
        return RC_ERR_NULL_PTR;
    if (!arr)
        return RC_ERR_INVALID_ARG;
    if (point3d_array_is_empty(arr))
        return RC_ERR_EMPTY_DATA;

    int rc = point3d_array_sum(center, arr);

    if (rc == RC_OK)
        rc = point3d_scale(center, 1.0 / point3d_array_get_count(arr));

    return rc;
}

int point3d_array_rotate(Point3DArray_t* arr, double angle, Axis_t axis) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (point3d_array_is_empty(arr))
        return RC_ERR_EMPTY_DATA;

    Point3D_t center;
    point3d_array_calc_center(&center, arr);

    RotationParams_t params = rotation_params_init(&center, angle, axis);

    Point3DArray_t copy;
    point3d_array_init(&copy);

    int rc = point3d_array_copy(&copy, arr);

    if (rc == RC_OK) {
        rc = apply_rotation(&copy, &params);
        if (rc == RC_OK)
            point3d_array_swap(arr, &copy);
        point3d_array_free(&copy);
    }

    return rc;
}

static int is_vertex_line(const char* line) {
    if (!line)
        return 0;

    return strncmp(line, OBJ_VERTEX_PREFIX, OBJ_VERTEX_PREFIX_LEN) == 0;
}

static int count_vertices(unsigned* count, FILE* file) {
    if (!count)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    char* line = NULL;
    size_t len = 0;

    *count = 0;

    while (getline(&line, &len, file) != -1)
        if (is_vertex_line(line))
            (*count)++;

    free(line);
    rewind(file);

    return RC_OK;
}

static int parse_vertex_line(Point3D_t* point, const char* line) {
    if (!point)
        return RC_ERR_NULL_PTR;
    if (!line)
        return RC_ERR_INVALID_ARG;

    double x, y, z;

    if (sscanf(line, OBJ_VERTEX_FORMAT, &x, &y, &z) != OBJ_VERTEX_FIELD_COUNT)
        return RC_ERR_PARSE;

    *point = point3d_init(x, y, z);

    return RC_OK;
}

static int read_vertices(Point3D_t* arr, FILE* file) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    char* line = NULL;
    size_t len = 0;
    unsigned index = 0;
    int rc = RC_OK;

    while (rc == RC_OK && getline(&line, &len, file) != -1) {
        if (is_vertex_line(line)) {
            Point3D_t point;
            rc = parse_vertex_line(&point, line);
            if (rc == RC_OK)
                rc = point3d_array_set(arr, index++, &point);
        }
    }

    free(line);
    rewind(file);

    return rc;
}

int point3d_array_read_obj(Point3DArray_t* arr, FILE* file) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    unsigned count = 0;
    int rc = count_vertices(&count, file);

    if (rc == RC_OK)
        rc = point3d_array_alloc(arr, count);

    if (rc == RC_OK) {
        rc = read_vertices(arr->data, file);
        if (rc != RC_OK)
            point3d_array_free(arr);
    }

    return rc;
}

static void write_point(const Point3D_t* point, FILE* file) {
    if (!point || !file) return;

    fprintf(file, SERIALIZER_VERTEX_FORMAT,
        point3d_get_x(point), point3d_get_y(point), point3d_get_z(point)
    );
}

int point3d_array_write_obj(const Point3DArray_t* arr, FILE* file) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    int rc = RC_OK;
    unsigned count = point3d_array_get_count(arr);

    for (unsigned i = 0; rc == RC_OK && i < count; i++) {
        Point3D_t point;
        rc = point3d_array_get(&point, arr, i);
        if (rc == RC_OK)
            write_point(&point, file);
    }

    return rc;
}
