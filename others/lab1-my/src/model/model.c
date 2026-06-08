#include <stdlib.h>

#include "model.h"

void model_init(Model_t* model) {
    if (!model) return;

    point3d_array_init(&model->points);
    edge_array_init(&model->edges);
}

int model_alloc(Model_t* model, unsigned points_count, unsigned edges_count) {
    if (!model)
        return RC_ERR_NULL_PTR;

    int rc = point3d_array_alloc(&model->points, points_count);
    if (rc == RC_OK) {
        rc = edge_array_alloc(&model->edges, edges_count);
        if (rc != RC_OK)
            point3d_array_free(&model->points);
    }

    return rc;
}

void model_free(Model_t* model) {
    if (!model) return;

    point3d_array_free(&model->points);
    edge_array_free(&model->edges);
}

int model_move(Model_t* model, const MoveData_t* move_data) {
    if (!model)
        return RC_ERR_NULL_PTR;
    if (!move_data)
        return RC_ERR_INVALID_ARG;

    Point3D_t delta_point = point3d_init_axis(move_data->delta, move_data->axis);

    return point3d_array_move(&model->points, &delta_point);
}

int model_scale(Model_t* model, const ScaleData_t* scale_data) {
    if (!model)
        return RC_ERR_NULL_PTR;
    if (!scale_data)
        return RC_ERR_INVALID_ARG;

    return point3d_array_scale(&model->points, scale_data->factor);
}

int model_rotate(Model_t* model, const RotateData_t* rotate_data) {
    if (!model)
        return RC_ERR_NULL_PTR;
    if (!rotate_data)
        return RC_ERR_INVALID_ARG;

    double angle_rad = rotate_data->angle * MATH_DEG_TO_RAD;
    return point3d_array_rotate(&model->points, angle_rad, rotate_data->axis);
}

void model_swap(Model_t* a, Model_t* b) {
    if (!a || !b) return;

    Model_t tmp = *a;
    *a = *b;
    *b = tmp;
}

static int model_read(Model_t* model, FILE* file) {
    if (!model)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    int rc = point3d_array_read_obj(&model->points, file);
    if (rc == RC_OK) {
        rc = edge_array_read_obj(&model->edges, file);
        if (rc != RC_OK)
            point3d_array_free(&model->points);
    }

    return rc;
}

int model_load(Model_t* model, const char* filename) {
    if (!model)
        return RC_ERR_NULL_PTR;
    if (!filename)
        return RC_ERR_INVALID_ARG;

    int rc = RC_OK;

    FILE* file = fopen(filename, "r");
    if (!file)
        rc = RC_ERR_OPEN_FILE;

    if (rc == RC_OK) {
        Model_t tmp;
        model_init(&tmp);

        rc = model_read(&tmp, file);

        fclose(file);

        if (rc == RC_OK) {
            model_swap(model, &tmp);
            model_free(&tmp);
        }
    }

    return rc;
}

static int model_write(const Model_t* model, FILE* file) {
    if (!model)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    int rc = point3d_array_write_obj(&model->points, file);
    if (rc == RC_OK)
        rc = edge_array_write_obj(&model->edges, file);

    return rc;
}

int model_save(const Model_t* model, const char* filename) {
    if (!model)
        return RC_ERR_NULL_PTR;
    if (!filename)
        return RC_ERR_INVALID_ARG;

    int rc = RC_OK;

    FILE* file = fopen(filename, "w");
    if (!file)
        rc = RC_ERR_OPEN_FILE;

    if (rc == RC_OK) {
        rc = model_write(model, file);

        fclose(file);
    }

    return rc;
}

int model_draw(const Model_t* model, const DrawRequest_t* params) {
    if (!model)
        return RC_ERR_NULL_PTR;
    if (!params)
        return RC_ERR_INVALID_ARG;

    return drawer_draw(params, &model->points, &model->edges);
}
