//
// Паттерн Command (сайт seregaukr): получатель — SceneManager — в конструкторе.
// Возврат через ссылку на внешнюю структуру FigureInternalData (out-параметр).
//

#ifndef FIGURECOMMANDGETINTERNALDATA_HPP
#define FIGURECOMMANDGETINTERNALDATA_HPP

#include <memory>
#include <vector>
#include <utility>

#include "../Commands/FigureCommand/BaseFigureCommand.hpp"
#include "../Managers/SceneManager/SceneManager.hpp"
#include "../InternalRepresentation/InternalDataVisitor.hpp"

struct FigureInternalData
{
    std::vector<Point>                      points;
    std::vector<std::pair<size_t, size_t>>  links;
    bool valid = false;
};

class FigureCommandGetInternalData : public BaseFigureCommand
{
public:
    FigureCommandGetInternalData(std::shared_ptr<SceneManager> manager,
                                 FigureInternalData&           out,
                                 size_t                        id)
        : _manager(std::move(manager)), _out(out), _id(id) {}

    ~FigureCommandGetInternalData() override = default;

    void execute() override
    {
        auto obj = _manager->getFigureByID(_id);
        if (!obj) return;

        InternalDataVisitor visitor;
        obj->accept(visitor);

        _out.points = visitor.getPointsList();
        _out.links  = visitor.getLinksList();
        _out.valid  = true;
    }

private:
    std::shared_ptr<SceneManager> _manager;
    FigureInternalData&           _out;
    size_t                        _id;
};

#endif //FIGURECOMMANDGETINTERNALDATA_HPP
