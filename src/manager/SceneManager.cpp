#include "manager/SceneManager.h"
#include "composite/CompositeObject.h"
#include "composite/Camera.h"
#include "bridge/CameraImpl.h"
#include "data/Point.h"
#include "composite/Light.h"
#include "exception/Exceptions.h"
#include "manager/HistoryManager.h"
#include <algorithm>

#include <memory>

void SceneManager::setScene(const ObjectPtr& obj) {
    auto composite = std::dynamic_pointer_cast<CompositeObject>(obj);
    if (!composite) {
        throw InvalidSceneError(__FILE__, "SceneManager", __FUNCTION__);
    }
    _scene.clear();
    _activeCamera.reset();
    for (auto it = composite->begin(); it != composite->end(); ++it) {
        if (*it) {
            _scene.addObject(*it);
        }
    }
}

void SceneManager::addObject(const ObjectPtr& obj) {
    if (!obj) {
        throw NullObjectError(__FILE__, "SceneManager", __FUNCTION__);
    }
    _scene.addObject(obj);
}

void SceneManager::removeObject(size_t id) {
    for (auto it = _scene.begin(); it != _scene.end(); ++it) {
        if (*it && (*it)->getId() == id) {
            _scene.removeObject(it);
            return;
        }
    }
    throw ObjectNotFoundError(id, __FILE__, "SceneManager", __FUNCTION__);
}

SceneManager::ObjectPtr SceneManager::getObject(size_t id) const {
    for (auto & it : _scene) {
        if (it && it->getId() == id) {
            return it;
        }
    }
    throw ObjectNotFoundError(id, __FILE__, "SceneManager", __FUNCTION__);
}

std::vector<SceneManager::ObjectPtr> SceneManager::getObjects() const {
    std::vector<ObjectPtr> result;
    for (auto & it : _scene) {
        result.push_back(it);
    }
    return result;
}

void SceneManager::setActiveCamera(size_t id) {
    auto cam = std::dynamic_pointer_cast<Camera>(getObject(id));
    if (!cam) {
        throw InvalidCameraError(id, __FILE__, "SceneManager", __FUNCTION__);
    }
    _activeCamera = cam;
}

void SceneManager::addDefaultCamera() {
    auto impl = std::make_unique<CameraImpl>(
        Point(0.0, 0.0, -10.0),
        Point(0.0, 0.0,  1.0),
        Point(0.0, 1.0,  0.0)
    );
    auto cam = std::make_shared<Camera>(std::move(impl));
    const size_t id = cam->getId();
    addObject(cam);
    setActiveCamera(id);
}

std::shared_ptr<Camera> SceneManager::getActiveCamera() const noexcept {
    return _activeCamera.lock();
}

std::shared_ptr<CompositeObject> SceneManager::buildVisibleComposite() const {
    auto group = std::make_shared<CompositeObject>();
    for (auto & it : _scene) {
        if (it && it->isVisible()) {
            group->add(it);
        }
    }
    return group;
}

std::shared_ptr<CompositeObject> SceneManager::buildInvisibleComposite() const {
    auto group = std::make_shared<CompositeObject>();
    for (auto & it : _scene) {
        if (it && !it->isVisible()) {
            group->add(it);
        }
    }
    return group;
}

void SceneManager::clear() {
    _activeCamera.reset();
    _scene.clear();
}

void SceneManager::clear(HistoryManager& historyMgr) {
    clear();
    historyMgr.clear();
}

void SceneManager::addLight(const std::shared_ptr<Light>& light) {
    if (!light) throw NullObjectError(__FILE__, "SceneManager", __FUNCTION__);
    _lights.push_back(light);
}

void SceneManager::removeLight(const std::shared_ptr<Light>& light) {
    _lights.erase(std::remove(_lights.begin(), _lights.end(), light), _lights.end());
}

void SceneManager::addCamera(const ObjectPtr& cam)
{
    if (!cam) {
        throw NullObjectError(__FILE__, "SceneManager", __FUNCTION__);
    }
    _scene.addObject(cam);
    setActiveCamera(cam->getId());
}
