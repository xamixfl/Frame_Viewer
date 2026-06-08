#include "scene.h"


Scene::Scene(std::vector<std::shared_ptr<Object>> _objects)
    : objects(std::move(_objects))
{}

void Scene::add_object(const std::shared_ptr<Object> &obj)
{
    objects.push_back(obj);
}

void Scene::remove_object(const iterator &it)
{
    objects.erase(it);
}

void Scene::clear_scene()
{
    objects.clear();
}

Scene::iterator Scene::begin()
{
    return objects.begin();
}

Scene::iterator Scene::end()
{
    return objects.end();
}

Scene::const_iterator Scene::begin() const
{
    return objects.begin();
}

Scene::const_iterator Scene::end() const
{
    return objects.end();
}

Scene::const_iterator Scene::cbegin() const
{
    return objects.cbegin();
}

Scene::const_iterator Scene::cend() const
{
    return objects.cend();
}

Scene::size_type Scene::size() const
{
    return objects.size();
}
