#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <memory>
#include "../BaseManager.hpp"
#include "History/BaseHistory.hpp"
#include "History/History.hpp"
#include "Scene/Scene/Scene.hpp"

class SceneManager : public BaseManager
{
public:
    SceneManager() : _scene(std::make_shared<Scene>()), _history(std::make_shared<SceneHistory>()) {}
    SceneManager(const SceneManager&);
    SceneManager(SceneManager&&) noexcept;
    ~SceneManager() override = default;

    SceneManager& operator=(const SceneManager&);
    SceneManager& operator=(SceneManager&&) noexcept;

    void setScene(const std::shared_ptr<Scene>& scene) { _scene = scene; }
    std::shared_ptr<Scene> getScene() { return _scene; }

    void saveSnapshot()                { _history->save(_scene); }
    [[nodiscard]] bool canUndo() const { return _history->canUndo(); }
    [[nodiscard]] bool canRedo() const { return _history->canRedo(); }

    bool undo();
    bool redo();

    void addObject(const std::shared_ptr<BaseObject>& object) const { _scene->addObject(object); }
    void addCamera(const std::shared_ptr<BaseObject>& camera) const { _scene->addCamera(camera); }

    [[nodiscard]] std::shared_ptr<BaseObject> getFigureByID(size_t index) const;
    [[nodiscard]] std::shared_ptr<BaseObject> getCameraByID(size_t index) const;

    void removeObject(size_t id) const;
    void removeCamera(size_t id) const;

    [[nodiscard]] size_t objectsSize() const { return _scene->objectsSize(); }
    [[nodiscard]] size_t camerasSize() const { return _scene->camerasSize(); }

private:
    std::shared_ptr<Scene>        _scene;
    std::shared_ptr<SceneHistory> _history;
};

#endif //SCENEMANAGER_HPP
