// LightCommands.cpp
#include "LightCommands.h"
#include "manager/SceneManager.h"
#include "composite/Light.h"

AddLightCommand::AddLightCommand(SceneManager& sceneMgr, std::shared_ptr<Light> light)
    : _sceneMgr(sceneMgr), _light(light) {}

void AddLightCommand::execute() {
    _sceneMgr.addLight(_light);
}

void AddLightCommand::unexecute() {
    _sceneMgr.removeLight(_light);
}

std::string AddLightCommand::name() const {
    return "Add Light";
}

RemoveLightCommand::RemoveLightCommand(SceneManager& sceneMgr, std::shared_ptr<Light> light)
    : _sceneMgr(sceneMgr), _light(light) {}

void RemoveLightCommand::execute() {
    _sceneMgr.removeLight(_light);
}

void RemoveLightCommand::unexecute() {
    _sceneMgr.addLight(_light);
}

std::string RemoveLightCommand::name() const {
    return "Remove Light";
}
