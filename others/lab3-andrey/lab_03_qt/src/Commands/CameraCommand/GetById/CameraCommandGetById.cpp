//
// Created by nuelex on 25/05/25.
//

#include "CameraCommandGetById.hpp"

#include "../../../Exceptions/Commands/CommandsException.hpp"
#include "../../../Exceptions/Scene/SceneException.hpp"

void CameraCommandGetById::execute()
{
    try
    {
        _object = _manager->getCameraByID(_id);
    }
    catch (ErrorScene_out_of_range &e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorCommand_out_of_range(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}
