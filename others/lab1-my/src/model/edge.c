#include <stdlib.h>
#include <string.h>

#include "edge.h"

Edge_t edge_init(unsigned start, unsigned end) {
    Edge_t edge;

    edge.start_index = start;
    edge.end_index = end;

    return edge;
}

Edge_t edge_init_default(void) {
    return edge_init(0, 0);
}

unsigned edge_get_start(const Edge_t* edge) {
    if (!edge)
        return 0;

    return edge->start_index;
}

unsigned edge_get_end(const Edge_t* edge) {
    if (!edge)
        return 0;

    return edge->end_index;
}

void edge_array_init(EdgeArray_t* arr) {
    if (!arr) return;
    if (!edge_array_is_empty(arr)) return;

    arr->data = NULL;
    arr->count = 0;
}

int edge_array_alloc(EdgeArray_t* arr, unsigned count) {
    if (!arr)
        return RC_ERR_NULL_PTR;

    int rc = RC_OK;

    if (count == 0) {
        arr->data = NULL;
        arr->count = count;
    }
    else {
        Edge_t* data = (Edge_t*) malloc(sizeof(Edge_t) * count);
        if (!data)
            rc = RC_ERR_ALLOC;
        else {
            arr->data = data;
            arr->count = count;
        }
    }

    return rc;
}

void edge_array_free(EdgeArray_t* arr) {
    if (!arr) return;

    free(arr->data);
    arr->data = NULL;
    arr->count = 0;
}

unsigned edge_array_get_count(const EdgeArray_t* arr) {
    if (!arr)
        return 0;

    return arr->count;
}

int edge_array_is_empty(const EdgeArray_t* arr) {
    if (!arr)
        return 1;

    return (arr->data == NULL || arr->count == 0);
}

int edge_array_get(Edge_t* edge, const EdgeArray_t* arr, unsigned index) {
    if (!edge)
        return RC_ERR_NULL_PTR;
    if (!arr)
        return RC_ERR_INVALID_ARG;
    if (index >= arr->count)
        return RC_ERR_OUT_OF_RANGE;

    *edge = arr->data[index];

    return RC_OK;
}

int edge_array_set(EdgeArray_t* arr, unsigned index, const Edge_t* edge) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!edge)
        return RC_ERR_INVALID_ARG;
    if (index >= arr->count)
        return RC_ERR_OUT_OF_RANGE;

    arr->data[index] = *edge;

    return RC_OK;
}

int edge_array_copy(EdgeArray_t* dst, const EdgeArray_t* src) {
    if (!dst)
        return RC_ERR_NULL_PTR;
    if (!src)
        return RC_ERR_INVALID_ARG;

    int rc = edge_array_alloc(dst, src->count);

    if (rc == RC_OK && src->count > 0)
        memcpy(dst->data, src->data, sizeof(Edge_t) * src->count);

    return rc;
}

static int count_spaces(const char* str) {
    if (!str)
        return 0;

    int count = 0;

    while (*str) {
        if (*str == ' ')
            count++;
        str++;
    }

    return count;
}

static int is_face_line(const char* line) {
    if (!line)
        return 0;

    return strncmp(line, OBJ_FACE_PREFIX, OBJ_FACE_PREFIX_LEN) == 0;
}

static int is_line_element(const char* line) {
    if (!line)
        return 0;

    return strncmp(line, OBJ_LINE_ELEMENT_PREFIX, OBJ_LINE_ELEMENT_PREFIX_LEN) == 0;
}

static int count_face_edges(const char* line) {
    if (!line)
        return 0;

    return count_spaces(line);
}

static int count_line_element_edges(const char* line) {
    if (!line)
        return 0;

    int spaces = count_spaces(line);

    return (spaces > 1) ? spaces - 1 : 0;
}

static int count_edges_in_file(unsigned* count, FILE* file) {
    if (!count)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    char* line = NULL;
    size_t len = 0;

    *count = 0;

    while (getline(&line, &len, file) != -1) {
        if (is_face_line(line))
            (*count) += count_face_edges(line);
        else if (is_line_element(line))
            (*count) += count_line_element_edges(line);
    }

    free(line);
    rewind(file);

    return RC_OK;
}

static void skip_non_digits(const char** ptr) {
    if (!ptr || !*ptr)
        return;

    while (**ptr && **ptr != ' ')
        (*ptr)++;
}

static int read_first_index(int* index, const char** ptr) {
    if (!index)
        return RC_ERR_NULL_PTR;
    if (!ptr || !*ptr)
        return RC_ERR_INVALID_ARG;

    int offset;
    int rc = RC_OK;

    if (sscanf(*ptr, "%d%n", index, &offset) != 1)
        rc = RC_ERR_PARSE;
    else {
        *ptr += offset;
        skip_non_digits(ptr);
    }

    return rc;
}

static int add_edge_at(EdgeArray_t* arr, unsigned* index, int start, int end) {
    if (!arr || !index)
        return RC_ERR_NULL_PTR;

    Edge_t edge = edge_init(start - 1, end - 1);
    int rc = edge_array_set(arr, *index, &edge);

    if (rc == RC_OK)
        (*index)++;

    return rc;
}

static int read_edges_chain(EdgeArray_t* arr, unsigned* e_index, int* current_v, const char* ptr) {
    if (!arr || !current_v || !e_index)
        return RC_ERR_NULL_PTR;
    if (!ptr)
        return RC_ERR_INVALID_ARG;

    int next_v;
    int offset;
    int rc = RC_OK;

    while (rc == RC_OK && sscanf(ptr, "%d%n", &next_v, &offset) == 1) {
        rc = add_edge_at(arr, e_index, *current_v, next_v);
        *current_v = next_v;
        ptr += offset;
        skip_non_digits(&ptr);
    }

    return rc;
}

static int parse_face_edges(EdgeArray_t* arr, unsigned* e_index, const char* line) {
    if (!arr || !e_index)
        return RC_ERR_NULL_PTR;
    if (!line)
        return RC_ERR_INVALID_ARG;

    const char* ptr = line + OBJ_FACE_PREFIX_LEN;
    int first_v;

    int rc = read_first_index(&first_v, &ptr);
    int current_v = first_v;

    if (rc == RC_OK)
        rc = read_edges_chain(arr, e_index, &current_v, ptr);

    if (rc == RC_OK)
        rc = add_edge_at(arr, e_index, current_v, first_v);

    return rc;
}

static int parse_line_element_edges(EdgeArray_t* arr, unsigned* e_index, const char* line) {
    if (!arr || !e_index)
        return RC_ERR_NULL_PTR;
    if (!line)
        return RC_ERR_INVALID_ARG;

    const char* ptr = line + OBJ_LINE_ELEMENT_PREFIX_LEN;
    int first_v;

    int rc = read_first_index(&first_v, &ptr);
    int current_v = first_v;

    if (rc == RC_OK)
        rc = read_edges_chain(arr, e_index, &current_v, ptr);

    return rc;
}

static int parse_edge_line(EdgeArray_t* arr, unsigned* e_index, const char* line) {
    if (!arr || !e_index)
        return RC_ERR_NULL_PTR;
    if (!line)
        return RC_ERR_INVALID_ARG;

    int rc = RC_OK;

    if (is_face_line(line))
        rc = parse_face_edges(arr, e_index, line);
    else if (is_line_element(line))
        rc = parse_line_element_edges(arr, e_index, line);

    return rc;
}

static int read_edges_from_file(EdgeArray_t* arr, FILE* file) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    char* line = NULL;
    size_t len = 0;
    unsigned e_index = 0;
    int rc = RC_OK;

    while (rc == RC_OK && getline(&line, &len, file) != -1)
        rc = parse_edge_line(arr, &e_index, line);

    free(line);
    rewind(file);

    return rc;
}

int edge_array_read_obj(EdgeArray_t* arr, FILE* file) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    unsigned count = 0;
    int rc = count_edges_in_file(&count, file);

    if (rc == RC_OK)
        rc = edge_array_alloc(arr, count);

    if (rc == RC_OK) {
        rc = read_edges_from_file(arr, file);
        if (rc != RC_OK)
            edge_array_free(arr);
    }

    return rc;
}

static void write_edge(const Edge_t* edge, FILE* file) {
    if (!edge || !file) return;

    fprintf(file, SERIALIZER_EDGE_FORMAT,
        edge_get_start(edge) + 1, edge_get_end(edge) + 1
    );
}

int edge_array_write_obj(const EdgeArray_t* arr, FILE* file) {
    if (!arr)
        return RC_ERR_NULL_PTR;
    if (!file)
        return RC_ERR_INVALID_ARG;

    int rc = RC_OK;
    unsigned count = edge_array_get_count(arr);

    Edge_t edge;
    for (unsigned i = 0; rc == RC_OK && i < count; i++) {
        rc = edge_array_get(&edge, arr, i);
        if (rc == RC_OK)
            write_edge(&edge, file);
    }

    return rc;
}
