#ifndef FIGURECOMMANDGETBYID_HPP
#define FIGURECOMMANDGETBYID_HPP

#include <cstddef>
#include "../BaseFigureCommand.hpp"
#include "../../../Managers/SceneManager/SceneManager.hpp"

class FigureCommandGetById : public BaseFigureCommand
{
public:
    FigureCommandGetById(std::shared_ptr<SceneManager>  manager,
                         std::shared_ptr<BaseObject>&   object,
                         size_t                         id)
        : _manager(std::move(manager)), _object(object), _id(id) {}

    ~FigureCommandGetById() override = default;

    void execute() override;

private:
    std::shared_ptr<SceneManager>  _manager;
    std::shared_ptr<BaseObject>&   _object;
    size_t                         _id;
};

#endif // FIGURECOMMANDGETBYID_HPP
