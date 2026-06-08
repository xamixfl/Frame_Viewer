#ifndef SCENEMANAGERSAVESNAPSHOTCOMMAND_HPP
#define SCENEMANAGERSAVESNAPSHOTCOMMAND_HPP

#include "../../BaseCommand.hpp"
#include "../../../Managers/SceneManager/SceneManager.hpp"

class SceneManagerSaveSnapshotCommand : public BaseCommand
{
public:
    explicit SceneManagerSaveSnapshotCommand(std::shared_ptr<SceneManager> manager)
        : _manager(std::move(manager)) {}

    ~SceneManagerSaveSnapshotCommand() override = default;

    void execute() override
    {
        _manager->saveSnapshot();
    }

private:
    std::shared_ptr<SceneManager> _manager;
};

#endif // SCENEMANAGERSAVESNAPSHOTCOMMAND_HPP
