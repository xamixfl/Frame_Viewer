//
// Created by nuelex on 25/05/25.
//

#include "SceneManagerCommandGetScene.hpp"

void SceneManagerCommandGetScene::execute()
{
    _scene = _manager->getScene();
}
