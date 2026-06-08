//
// Паттерн Command (сайт seregaukr / cpp-reference.ru): получатель — DrawManager —
// передаётся в конструктор и хранится в поле; в execute() напрямую вызываем
// нужный метод получателя.
//

#ifndef DRAWCOMMAND_HPP
#define DRAWCOMMAND_HPP

#include <memory>

#include "BaseDrawCommand.hpp"
#include "../../Managers/DrawManager/DrawManager.hpp"
#include "../../Managers/SceneManager/Scene/Scene/Scene.hpp"
#include "../../Drawer/Factory/AbstractDrawerFactory.hpp"
#include "../../HLR/BaseHLRStrategy.hpp"
#include "../../HLR/AllEdgesStrategy.hpp"

class DrawCommand : public BaseDrawCommand
{
public:
    DrawCommand(std::shared_ptr<DrawManager>                  manager,
                const std::shared_ptr<Scene>&                 scene,
                const std::shared_ptr<AbstractDrawerFactory>& factory,
                std::shared_ptr<BaseHLRStrategy>              hlr
                    = std::make_shared<AllEdgesStrategy>())
        : _manager(std::move(manager))
        , _scene(scene)
        , _factory(factory)
        , _hlr(std::move(hlr))
    {}

    ~DrawCommand() override = default;

    void execute() override;

private:
    std::shared_ptr<DrawManager>           _manager;
    std::shared_ptr<Scene>                 _scene;
    std::shared_ptr<AbstractDrawerFactory> _factory;
    std::shared_ptr<BaseHLRStrategy>       _hlr;
};

#endif //DRAWCOMMAND_HPP
