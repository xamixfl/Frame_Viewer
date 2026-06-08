#include "task_manager.h"

int task_manager(Request_t* request) {
    if (!request)
        return RC_ERR_NULL_PTR;

    static Model_t model;
    model_init(&model);

    int rc = RC_OK;

    switch (request->action) {
        case ACTION_LOAD:
            rc = model_load(&model, request->filename);
            break;
        case ACTION_SAVE:
            rc = model_save(&model, request->filename);
            break;
        case ACTION_MOVE:
            rc = model_move(&model, &request->move);
            break;
        case ACTION_ROTATE:
            rc = model_rotate(&model, &request->rotate);
            break;
        case ACTION_SCALE:
            rc = model_scale(&model, &request->scale);
            break;
        case ACTION_DRAW:
            rc = model_draw(&model, &request->draw_req);
            break;
        case ACTION_QUIT:
            model_free(&model);
            break;
        default:
            rc = RC_ERR_INVALID_ARG;
            break;
    }

    return rc;
}
