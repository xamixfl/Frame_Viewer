#ifndef MANAGERFACTORYINTERFACE_HPP
#define MANAGERFACTORYINTERFACE_HPP
#include <memory>

#include "../BaseFactory.hpp"
#include "../../Managers/LoadManager/LoadManager.hpp"
#include "../../Managers/SceneManager/SceneManager.hpp"
#include "../../Managers/DrawManager/DrawManager.hpp"


class ManagerFactoryInterface : public BaseFactory
{
public:
    ManagerFactoryInterface() = default;
    ~ManagerFactoryInterface() override = default;

    [[nodiscard]] virtual std::shared_ptr<SceneManager> createSceneManager() const = 0;
    [[nodiscard]] virtual std::shared_ptr<LoadManager> createLoadManager() const = 0;
    [[nodiscard]] virtual std::shared_ptr<DrawManager> createDrawManager() const = 0;
};



#endif //MANAGERFACTORYINTERFACE_HPP
