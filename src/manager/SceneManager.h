#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <cstddef>
#include <memory>
#include <vector>

#include "composite/BaseObject.h"
#include "composite/Scene.h"
#include "manager/BaseManager.h"
#include "composite/Light.h"
#include "bridge/BaseLightImpl.h"

class Camera;
class CompositeObject;
class HistoryManager;

class SceneManager final : public BaseManager {
public:
    using ObjectPtr = std::shared_ptr<BaseObject>;

    SceneManager() = default;
    ~SceneManager() override = default;

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    [[nodiscard]] Scene& getScene() noexcept { return _scene; }

    void setScene(const ObjectPtr& obj);

    void addObject(const ObjectPtr& obj);
    void removeObject(size_t id);

    [[nodiscard]] ObjectPtr getObject(size_t id) const;
    [[nodiscard]] std::vector<ObjectPtr> getObjects() const;

    void setActiveCamera(size_t id);
    [[nodiscard]] std::shared_ptr<Camera> getActiveCamera() const noexcept;

    void addDefaultCamera();

    void addLight(const std::shared_ptr<Light>& light);
    void removeLight(const std::shared_ptr<Light>& light);
    
    [[nodiscard]] std::shared_ptr<CompositeObject> buildVisibleComposite() const;
    [[nodiscard]] std::shared_ptr<CompositeObject> buildInvisibleComposite() const;

    void clear();
    void clear(HistoryManager& historyMgr);

private:
    Scene _scene;
    std::weak_ptr<Camera> _activeCamera;
    std::vector<std::shared_ptr<Light>> _lights;
};

#endif // SCENEMANAGER_H
