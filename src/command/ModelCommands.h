#ifndef MODELCOMMANDS_H
#define MODELCOMMANDS_H

#include <cstddef>
#include <string>

#include "command/ModelCommand.h"
#include "manager/LoadId.h"

class LoadManager;
class SceneManager;

class LoadModelCommand final : public ModelCommand {
public:
    LoadModelCommand(LoadManager& loadMgr, SceneManager& sceneMgr,
                     std::string filename, LoadId loadId = LoadId::Model) noexcept
        : _loadMgr(loadMgr), _sceneMgr(sceneMgr), _filename(std::move(filename)), _loadId(loadId) {}
    ~LoadModelCommand() override = default;

    void execute() override;
    [[nodiscard]] std::string name() const override {
        const char* repr = (_loadId == LoadId::ModelMatrix) ? " [matrix]" : " [list]";
        return "Load model: " + _filename + repr;
    }

private:
    LoadManager& _loadMgr;
    SceneManager& _sceneMgr;
    std::string _filename;
    LoadId _loadId;
};

class RemoveModelCommand final : public ModelCommand {
public:
    RemoveModelCommand(SceneManager& sceneMgr, size_t id) noexcept : _sceneMgr(sceneMgr), _id(id) {}
    ~RemoveModelCommand() override = default;

    void execute() override;
    [[nodiscard]] std::string name() const override { return "Remove model id=" + std::to_string(_id); }

private:
    SceneManager& _sceneMgr;
    size_t _id;
};

#endif 
