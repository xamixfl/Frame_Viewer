#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "common_types.h"
#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ACTION_LOAD,
    ACTION_SAVE,
    ACTION_MOVE,
    ACTION_ROTATE,
    ACTION_SCALE,
    ACTION_DRAW,
    ACTION_QUIT
} Action_t;

typedef struct {
    Action_t action;
    union {
        const char* filename;
        MoveData_t move;
        RotateData_t rotate;
        ScaleData_t scale;
        DrawRequest_t draw_req;
    };
} Request_t;

int task_manager(Request_t* request);

#ifdef __cplusplus
}
#endif

#endif // TASK_MANAGER_H
