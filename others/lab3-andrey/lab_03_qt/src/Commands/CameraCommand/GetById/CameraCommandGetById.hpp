#ifndef CAMERACOMMANDGETBYID_HPP
#define CAMERACOMMANDGETBYID_HPP

#include <cstddef>
#include <memory>
#include "../BaseCameraCommand.hpp"
#include "../../../Managers/SceneManager/SceneManager.hpp"

class CameraCommandGetById : public BaseCameraCommand
{
public:
    CameraCommandGetById(std::shared_ptr<SceneManager> manager,
                         std::shared_ptr<BaseObject>&  object,
                         size_t                        id)
        : _manager(std::move(manager)), _object(object), _id(id) {}

    ~CameraCommandGetById() override = default;

    void execute() override;

private:
    std::shared_ptr<SceneManager> _manager;  // receiver
    std::shared_ptr<BaseObject>&  _object;
    size_t                        _id;
};

#endif // CAMERACOMMANDGETBYID_HPP
