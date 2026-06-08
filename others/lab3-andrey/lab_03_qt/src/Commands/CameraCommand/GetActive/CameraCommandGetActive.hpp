//
// Created by nuelex on 25/05/25.
// Паттерн Command (сайт seregaukr): получатель в конструкторе.
// Возврат значения через ссылку на внешний объект (out-параметр конструктора).
//

#ifndef CAMERACOMMANDGETACTIVE_HPP
#define CAMERACOMMANDGETACTIVE_HPP

#include <memory>

#include "../BaseCameraCommand.hpp"
#include "../../../BaseObject/BaseObject.hpp"
#include "../../../Managers/DrawManager/DrawManager.hpp"

class CameraCommandGetActive : public BaseCameraCommand
{
public:
    CameraCommandGetActive(std::shared_ptr<DrawManager> manager,
                           std::shared_ptr<BaseObject>& object)
        : _manager(std::move(manager)), _object(object) {}

    ~CameraCommandGetActive() override = default;

    void execute() override;

private:
    std::shared_ptr<DrawManager>  _manager;
    std::shared_ptr<BaseObject>&  _object;
};

#endif //CAMERACOMMANDGETACTIVE_HPP
