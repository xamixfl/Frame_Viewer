#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <cstddef>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "manager/BaseManager.h"

class BaseObject;
class Memento;

struct Snapshot {
    std::shared_ptr<BaseObject> obj;
    std::shared_ptr<Memento> memento;
    std::string name;
};

class HistoryManager final : public BaseManager {
public:
    HistoryManager() = default;
    ~HistoryManager() override = default;

    HistoryManager(const HistoryManager&) = delete;
    HistoryManager& operator=(const HistoryManager&) = delete;

    void save(const std::shared_ptr<BaseObject>& obj, std::string name);

    bool undo();
    bool redo();

    [[nodiscard]] bool canUndo() const noexcept { return !_undo.empty(); }
    [[nodiscard]] bool canRedo() const noexcept { return !_redo.empty(); }

    [[nodiscard]] bool empty() const noexcept { return _undo.empty(); }
    [[nodiscard]] size_t size() const noexcept { return _undo.size(); }

    [[nodiscard]] std::vector<std::string> names() const;

    void clear() noexcept;

private:
    std::stack<Snapshot> _undo;
    std::stack<Snapshot> _redo;
};

#endif 
