#include "history_manager.h"


void HistoryManager::save(std::shared_ptr<Object> obj)
{
    undo_stack.push({obj, obj->create_snapshot()});

    while (!redo_stack.empty())
    {
        redo_stack.pop();
    }
}

void HistoryManager::undo()
{
    if (!can_undo())
    {
        throw std::runtime_error("Nothing to undo");
    }

    Snapshot snap = undo_stack.top();
    undo_stack.pop();

    redo_stack.push({snap.obj, snap.obj->create_snapshot()});

    snap.obj->restore_snapshot(snap.shapshot);
}

void HistoryManager::redo()
{
    if (!can_redo())
    {
        throw std::runtime_error("Nothing to redo");
    }
 
    Snapshot snap = redo_stack.top();
    redo_stack.pop();

    undo_stack.push({snap.obj, snap.obj->create_snapshot()});

    snap.obj->restore_snapshot(snap.shapshot);
}

bool HistoryManager::can_undo() const
{
    return !undo_stack.empty();
}
 
bool HistoryManager::can_redo() const
{
    return !redo_stack.empty();
}
