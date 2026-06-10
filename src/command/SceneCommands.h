#ifndef SCENECOMMANDS_H
#define SCENECOMMANDS_H

#include <string>

#include "command/SceneCommand.h"

class LoadManager;
class SceneManager;
class DrawManager;
class HistoryManager;

class LoadSceneCommand final : public SceneCommand {
public:
    LoadSceneCommand(LoadManager& loadMgr, SceneManager& sceneMgr,
                     HistoryManager& historyMgr, std::string filename) noexcept
        : _loadMgr(loadMgr), _sceneMgr(sceneMgr), _historyMgr(historyMgr), _filename(std::move(filename)) {}
    ~LoadSceneCommand() override = default;

    void execute() override;
    [[nodiscard]] std::string name() const override { return "Load scene: " + _filename;};

private:
    LoadManager& _loadMgr;
    SceneManager& _sceneMgr;
    HistoryManager& _historyMgr;
    std::string _filename;
};

class ClearSceneCommand final : public SceneCommand {
public:
    ClearSceneCommand(SceneManager& sceneMgr, HistoryManager& historyMgr) noexcept
        : _sceneMgr(sceneMgr), _historyMgr(historyMgr) {}
    ~ClearSceneCommand() override = default;

    void execute() override;
    [[nodiscard]] std::string name() const override { return "Clear scene"; }

private:
    SceneManager& _sceneMgr;
    HistoryManager& _historyMgr;
};

class DrawSceneCommand final : public SceneCommand {
public:
    DrawSceneCommand(SceneManager& sceneMgr, DrawManager& drawMgr) noexcept : _sceneMgr(sceneMgr), _drawMgr(drawMgr) {}
    ~DrawSceneCommand() override = default;

    void execute() override;
    [[nodiscard]] std::string name() const override { return "Draw scene"; }

private:
    SceneManager& _sceneMgr;
    DrawManager& _drawMgr;
};

#endif 
