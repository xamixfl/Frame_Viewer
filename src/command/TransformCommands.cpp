#include "command/TransformCommands.h"

#include "manager/HistoryManager.h"
#include "manager/TransformManager.h"

void MoveCommand::execute() {
    _transformMgr.moveGroup(_sceneMgr, _historyMgr, _ids, _transform, name());
}

void RotateCommand::execute() {
    _transformMgr.rotateGroup(_sceneMgr, _historyMgr, _ids, _transform, name());
}

void ScaleCommand::execute() {
    _transformMgr.scaleGroup(_sceneMgr, _historyMgr, _ids, _transform, name());
}
