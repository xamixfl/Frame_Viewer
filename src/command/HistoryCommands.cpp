#include "command/HistoryCommands.h"

#include "manager/HistoryManager.h"

void UndoCommand::execute() {
    _historyMgr.undo();
}

void RedoCommand::execute() {
    _historyMgr.redo();
}
