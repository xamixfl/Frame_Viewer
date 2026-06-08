#include "command/SceneCommands.h"
#include "manager/LoadManager.h"
#include "manager/SceneManager.h"
#include "manager/DrawManager.h"

void LoadSceneCommand::execute() {
    _loadMgr.loadScene(_sceneMgr, _historyMgr, _filename);
}

void ClearSceneCommand::execute() {
    _sceneMgr.clear(_historyMgr);
}

void DrawSceneCommand::execute() {
    _drawMgr.drawScene(_sceneMgr);
}
