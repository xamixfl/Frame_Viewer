#ifndef CAMERACOMMANDADD_HPP
#define CAMERACOMMANDADD_HPP

#include "../BaseCameraCommand.hpp"
#include "../../../Managers/SceneManager/SceneManager.hpp"

class CameraCommandAdd : public BaseCameraCommand
{
public:
    CameraCommandAdd(std::shared_ptr<SceneManager>     manager,
                     const BaseObject::shared_ptr_type& object)
        : _manager(std::move(manager)), _object(object) {}

    ~CameraCommandAdd() override = default;

    void execute() override;

private:
    std::shared_ptr<SceneManager>  _manager;
    BaseObject::shared_ptr_type    _object;
};

#endif // CAMERACOMMANDADD_HPP
