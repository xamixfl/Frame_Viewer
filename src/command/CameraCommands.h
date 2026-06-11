#ifndef CAMERACOMMANDS_H
#define CAMERACOMMANDS_H

#include <cstddef>
#include <string>

#include "command/CameraCommand.h"

class LoadManager;
class SceneManager;

class AddDefaultCameraCommand final : public CameraCommand {
public:
    explicit AddDefaultCameraCommand(SceneManager& sceneMgr) noexcept : _sceneMgr(sceneMgr) {}
    ~AddDefaultCameraCommand() override = default;

    void execute() override;

    [[nodiscard]] std::string name() const override { return "Add default camera"; }

private:
    SceneManager& _sceneMgr;
};

class RemoveCameraCommand final : public CameraCommand {
public:
    RemoveCameraCommand(SceneManager& sceneMgr, size_t id) noexcept : _sceneMgr(sceneMgr), _id(id) {}
    ~RemoveCameraCommand() override = default;

    void execute() override;
    [[nodiscard]] std::string name() const override { return "Remove camera id=" + std::to_string(_id); }

private:
    SceneManager& _sceneMgr;
    size_t _id;
};

class SwitchCameraCommand final : public CameraCommand {
public:
    SwitchCameraCommand(SceneManager& sceneMgr, size_t id) noexcept : _sceneMgr(sceneMgr), _id(id) {}
    ~SwitchCameraCommand() override = default;

    void execute() override;

    [[nodiscard]] std::string name() const override { return "Switch active camera id=" + std::to_string(_id); }

private:
    SceneManager& _sceneMgr;
    size_t _id;
};

#endif 
