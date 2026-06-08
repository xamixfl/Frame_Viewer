#ifndef SCENE_MANAGER_H__
#define SCENE_MANAGER_H__

#include "base_manager.h"
#include "scene.h"
#include "camera.h"
#include "model.h"


class SceneManager : public BaseManager
{
public:
    SceneManager() = default;
    explicit SceneManager(std::shared_ptr<Scene> _scene);
    ~SceneManager() override = default;

    void set_scene(std::shared_ptr<Scene> _scene);
    void set_camera(std::shared_ptr<Camera> _camera);

    void set_camera(std::size_t id);

    std::shared_ptr<Object> get_active_camera();
    std::shared_ptr<Scene> get_active_scene();

    void add_object(std::shared_ptr<Object> obj);

    void remove_model(std::size_t id);
    void remove_camera(std::size_t id);

    std::shared_ptr<Object> get_object(std::size_t id);

    std::shared_ptr<Object> create_group();

    void clear_scene();

private:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Camera> camera;
};

#endif
