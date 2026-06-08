#include "Scene.hpp"

std::shared_ptr<Scene> Scene::clone() const
{
    auto result = std::make_shared<Scene>();

    for (auto it = _objects.cbegin(); it != _objects.cend(); ++it)
        result->_objects.push_back((*it)->clone());

    for (auto it = _cameras.cbegin(); it != _cameras.cend(); ++it)
        result->_cameras.push_back((*it)->clone());

    return result;
}
