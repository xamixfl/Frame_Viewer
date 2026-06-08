#ifndef HISTORY_MANAGER_H__
#define HISTORY_MANAGER_H__

#include <stack>
#include <memory>

#include "base_manager.h"
#include "object.h"
#include "memento.h"


struct Snapshot
{
    std::shared_ptr<Object> obj;
    std::shared_ptr<Memento> shapshot;
};


class HistoryManager : public BaseManager
{
public:
    HistoryManager() = default;
    ~HistoryManager() override = default;

    void save(std::shared_ptr<Object> obj);

    void undo();
    void redo();

    bool can_undo() const;
    bool can_redo() const;

private:
    std::stack<Snapshot> undo_stack;
    std::stack<Snapshot> redo_stack;
};

#endif
