#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <stack>
#include <memory>
#include "BaseHistory.hpp"
#include "../Scene/Scene/Scene.hpp"

class SceneHistory : public BaseHistory
{
public:
    SceneHistory() = default;
    ~SceneHistory() override = default;

    void save(const std::shared_ptr<Scene>& scene)
    {
        _undo.push(scene->clone());
        while (!_redo.empty()) _redo.pop();
    }

    std::shared_ptr<Scene> undo(const std::shared_ptr<Scene>& current)
    {
        if (_undo.empty()) return nullptr;
        _redo.push(current->clone());
        auto snap = _undo.top();
        _undo.pop();
        return snap;
    }

    std::shared_ptr<Scene> redo(const std::shared_ptr<Scene>& current)
    {
        if (_redo.empty()) return nullptr;
        _undo.push(current->clone());
        auto snap = _redo.top();
        _redo.pop();
        return snap;
    }

    [[nodiscard]] bool canUndo() const noexcept { return !_undo.empty(); }
    [[nodiscard]] bool canRedo() const noexcept { return !_redo.empty(); }

private:
    std::stack<std::shared_ptr<Scene>> _undo;
    std::stack<std::shared_ptr<Scene>> _redo;
};

#endif //HISTORY_HPP
