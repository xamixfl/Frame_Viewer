#ifndef DRAWMANAGER_HPP
#define DRAWMANAGER_HPP

#include <memory>
#include "../BaseManager.hpp"
#include "../../BaseObject/Camera/Camera.hpp"
#include "../../Drawer/Factory/AbstractDrawerFactory.hpp"
#include "../../HLR/BaseHLRStrategy.hpp"
#include "../../HLR/AllEdgesStrategy.hpp"
#include "../SceneManager/Scene/Scene/Scene.hpp"

class DrawManager : public BaseManager
{
public:
    DrawManager() = default;
    ~DrawManager() override = default;

    void setCamera(const std::shared_ptr<BaseObject>& camera);
    [[nodiscard]] std::shared_ptr<BaseObject> getCamera() const { return _camera; }
    [[nodiscard]] bool IsEmpty() const { return (_camera == nullptr); }

    void drawScene(const std::shared_ptr<Scene>&                 scene,
                   const std::shared_ptr<AbstractDrawerFactory>& factory,
                   const std::shared_ptr<BaseHLRStrategy>&       hlr
                       = std::make_shared<AllEdgesStrategy>()) const;

    void clear(const std::shared_ptr<AbstractDrawerFactory>& factory) const;

private:
    std::shared_ptr<Camera> _camera;
};

#endif //DRAWMANAGER_HPP
