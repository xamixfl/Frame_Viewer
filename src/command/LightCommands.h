// LightCommands.h
#ifndef LIGHTCOMMANDS_H
#define LIGHTCOMMANDS_H

#include "command/BaseCommand.h"
#include <memory>

class SceneManager;
class Light;

class AddLightCommand final : public BaseCommand {
public:
    AddLightCommand(SceneManager& sceneMgr, std::shared_ptr<Light> light);
    ~AddLightCommand() override = default;

    void execute() override;
    void unexecute(); // или un-execute / undo, в зависимости от того, как у вас устроен вызов отмены
    std::string name() const override;

private:
    SceneManager& _sceneMgr;
    std::shared_ptr<Light> _light;
};

class RemoveLightCommand final : public BaseCommand {
public:
    RemoveLightCommand(SceneManager& sceneMgr, std::shared_ptr<Light> light);
    ~RemoveLightCommand() override = default;

    void execute() override;
    void unexecute();
    std::string name() const override;

private:
    SceneManager& _sceneMgr;
    std::shared_ptr<Light> _light;
};

#endif
