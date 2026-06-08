#ifndef FACADE_H__
#define FACADE_H__

#include "load_manager.h"
#include "draw_manager.h"
#include "transform_manager.h"
#include "scene_manager.h"
#include "history_manager.h"
#include "base_command.h"


class Facade
{
public:
    Facade() = default;
    Facade(LoadManager l, DrawManager d, TransformManager t, SceneManager s, HistoryManager h);
    ~Facade() = default;

    void execute(BaseCommand<LoadManager> &cmd);
    void execute(BaseCommand<DrawManager> &cmd);
    void execute(BaseCommand<TransformManager> &cmd);
    void execute(BaseCommand<SceneManager> &cmd);
    void execute(BaseCommand<HistoryManager> &cmd);

private:
    std::shared_ptr<LoadManager> _load;
    std::shared_ptr<DrawManager> _draw;
    std::shared_ptr<TransformManager> _transform;
    std::shared_ptr<SceneManager> _scene;
    std::shared_ptr<HistoryManager> _history;
};

#endif
