#ifndef MANAGERFACTORY_HPP
#define MANAGERFACTORY_HPP
#include <memory>

#include "ManagerFactoryInterface.hpp"
#include "../../Managers/LoadManager/LoadManager.hpp"
#include "../../Managers/SceneManager/SceneManager.hpp"


class ManagerFactory final: public ManagerFactoryInterface
{
public:
    ManagerFactory() = default;
    ~ManagerFactory() override = default;

    [[nodiscard]] std::shared_ptr<SceneManager> createSceneManager() const override;
    [[nodiscard]] std::shared_ptr<LoadManager> createLoadManager() const override;
    [[nodiscard]] std::shared_ptr<DrawManager> createDrawManager() const override;
};



#endif //MANAGERFACTORY_HPP
