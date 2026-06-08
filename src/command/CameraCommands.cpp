#include "command/CameraCommands.h"

#include "manager/LoadManager.h"
#include "manager/SceneManager.h"

void LoadCameraCommand::execute() {
    _loadMgr.loadCamera(_sceneMgr, _filename);
}

void AddDefaultCameraCommand::execute() {
    _sceneMgr.addDefaultCamera();
}

void RemoveCameraCommand::execute() {
    _sceneMgr.removeObject(_id);
}

void SwitchCameraCommand::execute() {
    _sceneMgr.setActiveCamera(_id);
}
