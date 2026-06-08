#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <math.h>

#include "common_types.h"
#include "obj_format.h"
#include "getline.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double x, y, z;
} Point3D_t;

typedef struct {
    Point3D_t* data;
    unsigned count;
} Point3DArray_t;

typedef struct {
    Point3D_t center;
    double angle;
    Axis_t axis;
} RotationParams_t;

Point3D_t point3d_init(double x, double y, double z);

Point3D_t point3d_init_default(void);

Point3D_t point3d_init_axis(double value, Axis_t axis);

double point3d_get_x(const Point3D_t* point);

double point3d_get_y(const Point3D_t* point);

double point3d_get_z(const Point3D_t* point);

RotationParams_t rotation_params_init(const Point3D_t* center, double angle, Axis_t axis);

int point3d_move(Point3D_t* point, const Point3D_t* delta);

int point3d_scale(Point3D_t* point, double factor);

int point3d_rotate(Point3D_t* point, const RotationParams_t* params);

void point3d_array_init(Point3DArray_t* arr);

int point3d_array_alloc(Point3DArray_t* arr, unsigned count);

void point3d_array_free(Point3DArray_t* arr);

int point3d_array_copy(Point3DArray_t* dst, const Point3DArray_t* src);

void point3d_array_swap(Point3DArray_t* a, Point3DArray_t* b);

int point3d_array_is_empty(const Point3DArray_t* arr);

unsigned point3d_array_get_count(const Point3DArray_t* arr);

int point3d_array_get(Point3D_t* point, const Point3DArray_t* arr, unsigned index);

int point3d_array_set(Point3D_t* arr, unsigned index, const Point3D_t* point);

int point3d_array_move(Point3DArray_t* arr, const Point3D_t* delta);

int point3d_array_scale(Point3DArray_t* arr, double factor);

int point3d_array_calc_center(Point3D_t* center, const Point3DArray_t* arr);

int point3d_array_rotate(Point3DArray_t* arr, double angle, Axis_t axis);

int point3d_array_read_obj(Point3DArray_t* arr, FILE* file);

int point3d_array_write_obj(const Point3DArray_t* arr, FILE* file);

#ifdef __cplusplus
}
#endif

#endif // POINT_H
