#ifndef SCENE_COMMANDS_H__
#define SCENE_COMMANDS_H__

#include "base_command.h"
#include "facade.h"
#include "concepts.h"

class Scene;


template<ReceiverClearScene Recevier>
class ClearScene : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)();

public:
    ClearScene();
    ~ClearScene() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    action method;
};


template<RecevierClearDrawScene Recevier>
class ClearDrawScene : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)();

public:
    ClearDrawScene();
    ~ClearDrawScene() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    action method;
};


template<ReceiverGetScene Recevier>
class GetScene : public BaseCommand<Recevier>
{
    using action = std::shared_ptr<Scene> (Recevier::*)();

public:
    GetScene() = default;
    explicit GetScene(std::shared_ptr<Scene> &_scene);
    ~GetScene() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Scene> &scene;
    action method;
};


template<ReceiverDrawScene Recevier>
class DrawScene : public BaseCommand<Recevier>
{
    using action = void (Recevier::*)(std::shared_ptr<Object>, std::shared_ptr<Camera>);

public:
    DrawScene() = default;
    DrawScene(std::shared_ptr<Scene> _scene, std::shared_ptr<Camera> _camera);
    ~DrawScene() override = default;

    void execute(std::shared_ptr<Recevier> r) override;
    std::string info() override;

private:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Camera> camera;
    action method;
};

#include "scene_commands.hpp"

#endif
