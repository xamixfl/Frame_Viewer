#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>

#include "common_types.h"
#include "obj_format.h"
#include "getline.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned start_index;
    unsigned end_index;
} Edge_t;

typedef struct {
    Edge_t* data;
    unsigned count;
} EdgeArray_t;

Edge_t edge_init(unsigned start, unsigned end);

Edge_t edge_init_default(void);

unsigned edge_get_start(const Edge_t* edge);

unsigned edge_get_end(const Edge_t* edge);

void edge_array_init(EdgeArray_t* arr);

int edge_array_alloc(EdgeArray_t* arr, unsigned count);

void edge_array_free(EdgeArray_t* arr);

int edge_array_is_empty(const EdgeArray_t* arr);

unsigned edge_array_get_count(const EdgeArray_t* arr);

int edge_array_get(Edge_t* edge, const EdgeArray_t* arr, unsigned index);

int edge_array_set(EdgeArray_t* arr, unsigned index, const Edge_t* edge);

int edge_array_copy(EdgeArray_t* dst, const EdgeArray_t* src);

int edge_array_read_obj(EdgeArray_t* arr, FILE* file);

int edge_array_write_obj(const EdgeArray_t* arr, FILE* file);

#ifdef __cplusplus
}
#endif

#endif // EDGE_H
