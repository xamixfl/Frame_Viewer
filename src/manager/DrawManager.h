#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <memory>

#include "manager/BaseManager.h"

class BaseObject;
class Camera;
class AbstractDrawerFactory;
class SceneManager;

class DrawManager final : public BaseManager {
public:
    explicit DrawManager(AbstractDrawerFactory& factory) noexcept;
    ~DrawManager() override = default;

    DrawManager(const DrawManager&) = delete;
    DrawManager& operator=(const DrawManager&) = delete;

    void draw(BaseObject& obj, std::shared_ptr<Camera> camera);
    void drawScene(SceneManager& sceneMgr);

private:
    AbstractDrawerFactory& _factory;
};

#endif // DRAWMANAGER_H
