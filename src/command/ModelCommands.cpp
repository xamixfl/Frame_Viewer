#include "command/ModelCommands.h"

#include "manager/LoadManager.h"
#include "manager/SceneManager.h"

void LoadModelCommand::execute() {
    _loadMgr.loadModel(_sceneMgr, _loadId, _filename);
}

void RemoveModelCommand::execute() {
    _sceneMgr.removeObject(_id);
}
