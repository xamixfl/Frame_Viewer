#include "manager/HistoryManager.h"

#include <ranges>
#include <utility>

#include "composite/BaseObject.h"
#include "memento/Memento.h"

void HistoryManager::save(const std::shared_ptr<BaseObject>& obj, std::string name) {
    if (!obj) {
        return;
    }
    _undo.push({obj, obj->createSnapshot(), std::move(name)});
    while (!_redo.empty()) {
        _redo.pop();
    }
}

bool HistoryManager::undo() {
    if (_undo.empty()) {
        return false;
    }
    Snapshot snap = std::move(_undo.top());
    _undo.pop();

    auto current = snap.obj->createSnapshot();
    _redo.push({snap.obj, std::move(current), snap.name});

    snap.obj->restoreSnapshot(snap.memento);
    return true;
}

bool HistoryManager::redo() {
    if (_redo.empty()) {
        return false;
    }
    Snapshot snap = std::move(_redo.top());
    _redo.pop();

    auto current = snap.obj->createSnapshot();
    _undo.push({snap.obj, std::move(current), snap.name});

    snap.obj->restoreSnapshot(snap.memento);
    return true;
}

std::vector<std::string> HistoryManager::names() const {
    std::vector<std::string> result;
    result.reserve(_undo.size());

    std::stack<Snapshot> copy = _undo;
    std::vector<std::string> reversed;
    reversed.reserve(copy.size());
    while (!copy.empty()) {
        reversed.push_back(copy.top().name);
        copy.pop();
    }
    for (auto & it : std::views::reverse(reversed)) {
        result.push_back(it);
    }
    return result;
}

void HistoryManager::clear() noexcept {
    while (!_undo.empty()) _undo.pop();
    while (!_redo.empty()) _redo.pop();
}
