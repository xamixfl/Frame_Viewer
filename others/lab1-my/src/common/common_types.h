#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Коды возврата. */
typedef enum {
    RC_OK = 0,
    RC_ERR_NULL_PTR,
    RC_ERR_INVALID_ARG,
    RC_ERR_ALLOC,
    RC_ERR_OUT_OF_RANGE,
    RC_ERR_OPEN_FILE,
    RC_ERR_READ_FILE,
    RC_ERR_WRITE_FILE,
    RC_ERR_PARSE,
    RC_ERR_PROJECTION,
    RC_ERR_EMPTY_DATA
} ReturnCode_t;

/* Оси координат. */
typedef enum {
    AXIS_X = 0,
    AXIS_Y = 1,
    AXIS_Z = 2
} Axis_t;

/* Математические константы. */
#define MATH_DEG_TO_RAD (M_PI / 180.0)
#define MATH_EPSILON 0.0001

/* Настройки управления. */
#define MOUSE_SENSITIVITY 0.3
#define MOVE_STEP 0.5
#define SCALE_UP 1.1
#define SCALE_DOWN 0.9

/* Настройки проекции. */
#define PROJECTION_SCALE_DIVISOR 3.0
#define PROJECTION_CENTER_DIVISOR 2.0
#define PROJECTION_Z_EPSILON 0.0001
#define PROJECTION_DEFAULT_DISTANCE 5.0

#ifdef __cplusplus
}
#endif

#endif // COMMON_TYPES_H
