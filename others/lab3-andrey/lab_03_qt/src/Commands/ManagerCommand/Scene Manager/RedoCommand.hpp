#ifndef REDOCOMMAND_HPP
#define REDOCOMMAND_HPP

#include "../../BaseCommand.hpp"
#include "../../../Managers/SceneManager/SceneManager.hpp"

class RedoCommand : public BaseCommand
{
public:
    RedoCommand(std::shared_ptr<SceneManager> manager, bool& success)
        : _manager(std::move(manager)), _success(success) {}

    ~RedoCommand() override = default;

    void execute() override
    {
        _success = _manager->redo();
    }

private:
    std::shared_ptr<SceneManager> _manager;
    bool& _success;
};

#endif // REDOCOMMAND_HPP
