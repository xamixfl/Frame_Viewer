//
// Created by nuelex on 23/05/25.
// Паттерн Command (сайт seregaukr): получатель в конструкторе.
//

#ifndef CAMERASETCOMMAND_HPP
#define CAMERASETCOMMAND_HPP

#include <memory>

#include "../BaseCameraCommand.hpp"
#include "../../../BaseObject/BaseObject.hpp"
#include "../../../Managers/DrawManager/DrawManager.hpp"

class CameraSetCommand : public BaseCameraCommand
{
public:
    CameraSetCommand(std::shared_ptr<DrawManager>       manager,
                     const std::shared_ptr<BaseObject>& object)
        : _manager(std::move(manager)), _camera(object) {}

    ~CameraSetCommand() override = default;

    void execute() override;

private:
    std::shared_ptr<DrawManager> _manager;
    std::shared_ptr<BaseObject>  _camera;
};

#endif //CAMERASETCOMMAND_HPP
