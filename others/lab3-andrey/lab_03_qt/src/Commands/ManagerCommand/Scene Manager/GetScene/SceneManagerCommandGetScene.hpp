//
// Created by nuelex on 25/05/25.
// Паттерн Command (сайт seregaukr): получатель в конструкторе.
// Возврат значения через ссылку на внешний объект (out-параметр конструктора).
//

#ifndef SCENEMANAGERCOMMANDGETSCENE_HPP
#define SCENEMANAGERCOMMANDGETSCENE_HPP

#include <memory>

#include "../BaseSceneManagerCommand.hpp"
#include "../../../../Managers/SceneManager/SceneManager.hpp"
#include "../../../../Managers/SceneManager/Scene/Scene/Scene.hpp"

class SceneManagerCommandGetScene : public BaseSceneManagerCommand
{
public:
    SceneManagerCommandGetScene(std::shared_ptr<SceneManager> manager,
                                std::shared_ptr<Scene>&       scene)
        : _manager(std::move(manager)), _scene(scene) {}

    ~SceneManagerCommandGetScene() override = default;

    void execute() override;

private:
    std::shared_ptr<SceneManager> _manager;
    std::shared_ptr<Scene>&       _scene;
};

#endif //SCENEMANAGERCOMMANDGETSCENE_HPP
