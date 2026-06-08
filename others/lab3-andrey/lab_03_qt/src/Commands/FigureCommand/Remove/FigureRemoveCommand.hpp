#ifndef FIGUREREMOVECOMMAND_HPP
#define FIGUREREMOVECOMMAND_HPP

#include <cstddef>
#include "../BaseFigureCommand.hpp"
#include "../../../Managers/SceneManager/SceneManager.hpp"

class FigureRemoveCommand : public BaseFigureCommand
{
public:
    FigureRemoveCommand(std::shared_ptr<SceneManager> manager, size_t id)
        : _manager(std::move(manager)), _id(id) {}

    ~FigureRemoveCommand() override = default;

    void execute() override;

private:
    std::shared_ptr<SceneManager> _manager;
    size_t _id;
};

#endif // FIGUREREMOVECOMMAND_HPP
