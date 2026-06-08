#include "scene_commands.h"

template<ReceiverClearScene Recevier>
ClearScene<Recevier>::ClearScene()
{
    method = &Recevier::clear_scene;
}

template<ReceiverClearScene Recevier>
void ClearScene<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)();
}

template<ReceiverClearScene Recevier>
std::string ClearScene<Recevier>::info()
{
    return "ClearScene";
}


template<RecevierClearDrawScene Recevier>
ClearDrawScene<Recevier>::ClearDrawScene()
{
    method = &Recevier::clear_scene;
}

template<RecevierClearDrawScene Recevier>
void ClearDrawScene<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    ((*r).*method)();
}

template<RecevierClearDrawScene Recevier>
std::string ClearDrawScene<Recevier>::info()
{
    return "ClearDrawScene";
}


template<ReceiverGetScene Recevier>
GetScene<Recevier>::GetScene(std::shared_ptr<Scene> &_scene)
    : scene(_scene)
{
    method = &Recevier::get_active_scene;
}

template<ReceiverGetScene Recevier>
void GetScene<Recevier>::execute(std::shared_ptr<Recevier> r)
{
    scene = ((*r).*method)();
}

template<ReceiverGetScene Recevier>
std::string GetScene<Recevier>::info()
{
    return "GetScene";
}


template<ReceiverDrawScene Recevier>
DrawScene<Recevier>::DrawScene(std::shared_ptr<Scene> _scene, std::shared_ptr<Camera> _camera)
    : scene(std::move(_scene)), camera(std::move(_camera))
{
    method = &Recevier::draw;
}

template<ReceiverDrawScene Recevier>
void DrawScene<Recevier>::execute(std::shared_ptr<Recevier> r)
{   
    for (auto &obj : *scene)
    {
        ((*r).*method)(obj, camera);
    }
}

template<ReceiverDrawScene Recevier>
std::string DrawScene<Recevier>::info()
{
    return "DrawScene";
}
