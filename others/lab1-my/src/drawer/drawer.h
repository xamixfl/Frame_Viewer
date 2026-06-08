#ifndef DRAWER_H
#define DRAWER_H

#include "common_types.h"
#include "projection.h"
#include "point.h"
#include "edge.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int width;
    int height;
} DrawSize_t;

typedef struct {
    void* canvas;
    DrawSize_t size;
} DrawRequest_t;

int drawer_draw(const DrawRequest_t* draw_data, const Point3DArray_t* points, const EdgeArray_t* edges);

#ifdef __cplusplus
}
#endif

#endif // DRAWER_H
