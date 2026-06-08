#include "SceneManager.hpp"

#include "../../Exceptions/Scene/SceneException.hpp"

SceneManager::SceneManager(const SceneManager& scene)
    : _scene(scene._scene)
    , _history(std::make_shared<SceneHistory>())
{
}

SceneManager::SceneManager(SceneManager&& scene) noexcept
    : _scene(std::move(scene._scene))
    , _history(std::move(scene._history))
{
    scene._scene = nullptr;
    scene._history = nullptr;
}

SceneManager& SceneManager::operator=(const SceneManager& scene)
{
    if (this != &scene)
    {
        _scene = scene._scene;
        _history = std::make_shared<SceneHistory>();
    }
    return *this;
}

SceneManager& SceneManager::operator=(SceneManager&& scene) noexcept
{
    if (this != &scene)
    {
        _scene = std::move(scene._scene);
        _history = std::move(scene._history);
        scene._scene = nullptr;
        scene._history = nullptr;
    }
    return *this;
}

bool SceneManager::undo()
{
    auto snap = _history->undo(_scene);
    if (!snap) return false;
    _scene = snap;
    return true;
}

bool SceneManager::redo()
{
    auto snap = _history->redo(_scene);
    if (!snap) return false;
    _scene = snap;
    return true;
}

std::shared_ptr<BaseObject> SceneManager::getFigureByID(size_t index) const
{
    if (index >= _scene->objectsSize())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorScene_out_of_range(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
    auto it = _scene->objectsBegin();
    std::advance(it, index);
    return *it;
}

std::shared_ptr<BaseObject> SceneManager::getCameraByID(size_t index) const
{
    if (index >= _scene->camerasSize())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorScene_out_of_range(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
    auto it = _scene->camerasBegin();
    std::advance(it, index);
    return *it;
}

void SceneManager::removeObject(size_t id) const
{
    if (id >= _scene->objectsSize())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorScene_out_of_range(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
    auto it = _scene->objectsBegin();
    std::advance(it, id);
    _scene->removeObject(it);
}

void SceneManager::removeCamera(size_t id) const
{
    if (id >= _scene->camerasSize())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorScene_out_of_range(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
    auto it = _scene->camerasBegin();
    std::advance(it, id);
    _scene->removeCamera(it);
}
