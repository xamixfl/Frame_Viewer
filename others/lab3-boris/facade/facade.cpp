#include "facade.h"


Facade::Facade(LoadManager l, DrawManager d, TransformManager t, SceneManager s, HistoryManager h)
    : _load(std::make_shared<LoadManager>(l)),
      _draw(std::make_shared<DrawManager>(d)),
      _transform(std::make_shared<TransformManager>(t)),
      _scene(std::make_shared<SceneManager>(s)),
      _history(std::make_shared<HistoryManager>(h))
{}

void Facade::execute(BaseCommand<LoadManager> &cmd)
{
    cmd.execute(_load);
}

void Facade::execute(BaseCommand<DrawManager> &cmd)
{
    cmd.execute(_draw);
}

void Facade::execute(BaseCommand<TransformManager> &cmd)
{
    cmd.execute(_transform);
}

void Facade::execute(BaseCommand<SceneManager> &cmd)
{
    cmd.execute(_scene);
}

void Facade::execute(BaseCommand<HistoryManager> &cmd)
{
    cmd.execute(_history);
}
