#include "command/CameraCommands.h"

#include "manager/LoadManager.h"
#include "manager/SceneManager.h"

void AddDefaultCameraCommand::execute() {
    _sceneMgr.addDefaultCamera();
}

void RemoveCameraCommand::execute() {
    _sceneMgr.removeObject(_id);
}

void SwitchCameraCommand::execute() {
    _sceneMgr.setActiveCamera(_id);
}
