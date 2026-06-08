//
// Created by nuelex on 23/05/25.
//

#include "CameraSetCommand.hpp"

#include "../../../Exceptions/Commands/CommandsException.hpp"
#include "../../../Exceptions/Managers/DrawManagerException.hpp"

void CameraSetCommand::execute()
{
    try
    {
        _manager->setCamera(_camera);
    }
    catch (ErrorDrawManager_invalid_camera&)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorCommand_invalid_data(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}
