#include "CameraCommandAdd.hpp"

#include "../../../Exceptions/Commands/CommandsException.hpp"
#include "../../../Exceptions/Scene/SceneException.hpp"

void CameraCommandAdd::execute()
{
    try
    {
        _manager->addCamera(_object);
    }
    catch (ErrorScene_bad_alloc& e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorCommand_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}
