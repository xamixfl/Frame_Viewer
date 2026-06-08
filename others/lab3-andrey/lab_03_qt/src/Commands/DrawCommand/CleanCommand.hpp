//
// Паттерн Command. Получатель (DrawManager) передаётся в конструктор и
// хранится в поле, как в Game-примере на cpp-reference.ru / сайт seregaukr.
// В execute() напрямую вызываем нужный метод получателя.
//

#ifndef CLEANCOMMAND_HPP
#define CLEANCOMMAND_HPP

#include <memory>

#include "BaseDrawCommand.hpp"
#include "../../Drawer/Factory/AbstractDrawerFactory.hpp"
#include "../../Managers/DrawManager/DrawManager.hpp"

class CleanCommand : public BaseDrawCommand
{
public:
    CleanCommand(std::shared_ptr<DrawManager>                  manager,
                 const std::shared_ptr<AbstractDrawerFactory>& factory)
        : _manager(std::move(manager)), _factory(factory) {}

    ~CleanCommand() override = default;

    void execute() override;

private:
    std::shared_ptr<DrawManager>           _manager;
    std::shared_ptr<AbstractDrawerFactory> _factory;
};

#endif //CLEANCOMMAND_HPP
