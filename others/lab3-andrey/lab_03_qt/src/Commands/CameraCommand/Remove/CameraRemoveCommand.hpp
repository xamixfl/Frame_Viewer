//
// Created by nuelex on 22/05/25.
// Паттерн Command (сайт seregaukr): получатель в конструкторе.
//

#ifndef CAMERAREMOVECOMMAND_HPP
#define CAMERAREMOVECOMMAND_HPP

#include <cstddef>
#include <memory>

#include "../BaseCameraCommand.hpp"
#include "../../../Managers/SceneManager/SceneManager.hpp"

class CameraRemoveCommand : public BaseCameraCommand
{
public:
    CameraRemoveCommand(std::shared_ptr<SceneManager> manager, size_t id)
        : _manager(std::move(manager)), _id(id) {}

    ~CameraRemoveCommand() override = default;

    void execute() override;

private:
    std::shared_ptr<SceneManager> _manager;
    size_t                        _id;
};

#endif //CAMERAREMOVECOMMAND_HPP
