//
// Created by nuelex on 22/05/25.
//

#include "CameraRemoveCommand.hpp"

#include "../../../Exceptions/Commands/CommandsException.hpp"
#include "../../../Exceptions/Scene/SceneException.hpp"

void CameraRemoveCommand::execute()
{
    try
    {
        _manager->removeCamera(_id);
    }
    catch (ErrorScene_out_of_range&)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorCommand_out_of_range(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}
