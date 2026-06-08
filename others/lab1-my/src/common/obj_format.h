#ifndef OBJ_FORMAT_H
#define OBJ_FORMAT_H

#ifdef __cplusplus
extern "C" {
#endif

#define OBJ_VERTEX_PREFIX "v "
#define OBJ_VERTEX_PREFIX_LEN 2
#define OBJ_FACE_PREFIX "f "
#define OBJ_FACE_PREFIX_LEN 2
#define OBJ_LINE_ELEMENT_PREFIX "l "
#define OBJ_LINE_ELEMENT_PREFIX_LEN 2
#define OBJ_VERTEX_FORMAT "v %lf %lf %lf"
#define OBJ_VERTEX_FIELD_COUNT 3

#define SERIALIZER_VERTEX_FORMAT "v %lf %lf %lf\n"
#define SERIALIZER_EDGE_FORMAT "l %u %u\n"

#ifdef __cplusplus
}
#endif

#endif // OBJ_FORMAT_H
