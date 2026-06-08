#include "composite/Scene.h"
#include "composite/BaseObject.h"

void Scene::addObject(const ObjectPtr& obj) {
    if (obj) {
        _objects.push_back(obj);
    }
}

void Scene::removeObject(iterator it) {
    if (it != _objects.end()) {
        _objects.erase(it);
    }
}

void Scene::clear() noexcept {
    _objects.clear();
}

Scene::iterator Scene::begin() noexcept { return _objects.begin(); }
Scene::iterator Scene::end() noexcept { return _objects.end(); }
Scene::const_iterator Scene::begin() const noexcept { return _objects.begin(); }
Scene::const_iterator Scene::end() const noexcept { return _objects.end(); }

std::size_t Scene::size() const noexcept { return _objects.size(); }
bool Scene::empty() const noexcept { return _objects.empty(); }
