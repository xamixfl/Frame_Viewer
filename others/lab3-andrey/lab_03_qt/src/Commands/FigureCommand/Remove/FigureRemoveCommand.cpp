#include "FigureRemoveCommand.hpp"

#include <typeinfo>
#include "../../../Exceptions/Commands/CommandsException.hpp"
#include "../../../Exceptions/Scene/SceneException.hpp"

void FigureRemoveCommand::execute()
{
    try
    {
        _manager->removeObject(_id);
    }
    catch (ErrorScene_out_of_range& e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorCommand_out_of_range(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}
