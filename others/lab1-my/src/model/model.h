#ifndef MODEL_H
#define MODEL_H

#include "common_types.h"
#include "drawer.h"
#include "point.h"
#include "edge.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    Point3DArray_t points;
    EdgeArray_t edges;
} Model_t;

typedef struct {
    double delta;
    Axis_t axis;
} MoveData_t;

typedef struct {
    double angle;
    Axis_t axis;
} RotateData_t;

typedef struct {
    double factor;
} ScaleData_t;

void model_init(Model_t* model);

int model_alloc(Model_t* model, unsigned points_count, unsigned edges_count);

void model_free(Model_t* model);

int model_move(Model_t* model, const MoveData_t* move_data);

int model_scale(Model_t* model, const ScaleData_t* scale_data);

int model_rotate(Model_t* model, const RotateData_t* rotate_data);

void model_swap(Model_t* a, Model_t* b);

int model_load(Model_t* model, const char* filename);

int model_save(const Model_t* model, const char* filename);

int model_draw(const Model_t* model, const DrawRequest_t* params);

#ifdef __cplusplus
}
#endif

#endif // MODEL_H
