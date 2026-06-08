#include <stdexcept>
#include "scene_manager.h"


SceneManager::SceneManager(std::shared_ptr<Scene> _scene)
    : scene(std::move(_scene))
{}

std::shared_ptr<Object> SceneManager::get_active_camera()
{
    return camera;
}

std::shared_ptr<Scene> SceneManager::get_active_scene()
{
    return scene;
}

void SceneManager::set_scene(std::shared_ptr<Scene> _scene)
{
    scene = _scene;
}

void SceneManager::set_camera(std::shared_ptr<Camera> _camera)
{
    camera = _camera;
}

void SceneManager::set_camera(std::size_t id)
{
    for (auto &obj : *scene)
    {
        if (obj->get_id() == id)
        {
            auto found_camera = std::dynamic_pointer_cast<Camera>(obj);

            if (found_camera == nullptr)
            {
                throw std::runtime_error("Object is not a camera");
            }

            camera = found_camera;
            return;
        }
    }
}

void SceneManager::add_object(std::shared_ptr<Object> obj)
{
    scene->add_object(obj);
}

void SceneManager::remove_model(std::size_t id)
{
    for (auto it = scene->begin(); it != scene->end(); ++it)
    {
        if ((*it)->get_id() == id)
        {
            if (!(*it)->is_drawable())
            {
                throw std::runtime_error("Object is not a model");
            }

            scene->remove_object(it);
            return;
        }
    }
}

void SceneManager::remove_camera(std::size_t id)
{
    for (auto it = scene->begin(); it != scene->end(); ++it)
    {
        if ((*it)->get_id() == id)
        {
            if ((*it)->is_drawable())
            {
                throw std::runtime_error("Object is not a camera");
            }

            scene->remove_object(it);
            return;
        }
    }
}

std::shared_ptr<Object> SceneManager::get_object(std::size_t id)
{
    for (auto &obj : *scene)
    {
        if (obj->get_id() == id)
        {
            return obj;
        }
    }

    throw std::runtime_error("Objject dont find");
}

std::shared_ptr<Object> SceneManager::create_group()
{
    std::vector<std::shared_ptr<Object>> objs;

    for (auto &obj : *scene)
    {
        if (obj->is_drawable())
        {
            objs.push_back(obj);
        }
    }

    std::shared_ptr<Object> group = std::make_shared<Composite>(objs);
    scene->add_object(group);
    return group;
}

void SceneManager::clear_scene()
{
    scene->clear_scene();
}
