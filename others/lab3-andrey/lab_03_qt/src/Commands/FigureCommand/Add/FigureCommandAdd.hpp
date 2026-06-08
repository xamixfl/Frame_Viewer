#ifndef FIGURECOMMANDADD_HPP
#define FIGURECOMMANDADD_HPP

#include "../BaseFigureCommand.hpp"
#include "../../../Managers/SceneManager/SceneManager.hpp"

class FigureCommandAdd : public BaseFigureCommand
{
public:
    FigureCommandAdd(std::shared_ptr<SceneManager>     manager,
                     const BaseObject::shared_ptr_type& object)
        : _manager(std::move(manager)), _object(object) {}

    ~FigureCommandAdd() override = default;

    void execute() override;

private:
    std::shared_ptr<SceneManager>  _manager;
    BaseObject::shared_ptr_type    _object;
};

#endif // FIGURECOMMANDADD_HPP
