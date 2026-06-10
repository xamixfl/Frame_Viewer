#ifndef TRANSFORMCOMMANDS_H
#define TRANSFORMCOMMANDS_H

#include <cstddef>
#include <string>
#include <vector>

#include "command/BaseCommand.h"
#include "data/Transform.h"

class SceneManager;
class TransformManager;
class HistoryManager;

class GroupTransformCommand : public BaseCommand {
public:
    GroupTransformCommand(SceneManager& sceneMgr, TransformManager& transformMgr,
                          HistoryManager& historyMgr,
                          std::vector<size_t> ids, const Transform& t) noexcept
        : _sceneMgr(sceneMgr), _transformMgr(transformMgr), _historyMgr(historyMgr),
          _ids(std::move(ids)), _transform(t) {}
    ~GroupTransformCommand() override = default;

protected:
    SceneManager& _sceneMgr;
    TransformManager& _transformMgr;
    HistoryManager& _historyMgr;
    std::vector<size_t> _ids;
    Transform _transform;

    [[nodiscard]] std::string _idsString() const {
        if (_ids.empty()) {
            return "[]";
        }
        if (_ids.size() == 1) {
            return "id=" + std::to_string(_ids.front());
        }
        std::string out = "group [";
        for (size_t i = 0; i < _ids.size(); ++i) {
            if (i) {
                out += ", ";
            }
            out += std::to_string(_ids[i]);
        }
        out += "]";
        return out;
    };
};

class MoveCommand final : public GroupTransformCommand {
public:
    using GroupTransformCommand::GroupTransformCommand;
    void execute() override;
    [[nodiscard]] std::string name() const override { return "Move " + _idsString(); }
};

class RotateCommand final : public GroupTransformCommand {
public:
    using GroupTransformCommand::GroupTransformCommand;
    void execute() override;
    [[nodiscard]] std::string name() const override { return "Rotate " + _idsString(); }
};

class ScaleCommand final : public GroupTransformCommand {
public:
    using GroupTransformCommand::GroupTransformCommand;
    void execute() override;
    [[nodiscard]] std::string name() const override { return "Scale " + _idsString(); }
};

#endif
