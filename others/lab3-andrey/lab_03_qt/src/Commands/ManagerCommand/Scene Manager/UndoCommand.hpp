#ifndef UNDOCOMMAND_HPP
#define UNDOCOMMAND_HPP

#include "../../BaseCommand.hpp"
#include "../../../Managers/SceneManager/SceneManager.hpp"

class UndoCommand : public BaseCommand
{
public:
    UndoCommand(std::shared_ptr<SceneManager> manager, bool& success)
        : _manager(std::move(manager)), _success(success) {}

    ~UndoCommand() override = default;

    void execute() override
    {
        _success = _manager->undo();
    }

private:
    std::shared_ptr<SceneManager> _manager;
    bool& _success;
};

#endif // UNDOCOMMAND_HPP
