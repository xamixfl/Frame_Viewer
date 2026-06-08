#include "DrawCommand.hpp"

#include "../../Exceptions/Managers/DrawManagerException.hpp"

void DrawCommand::execute()
{
    try
    {
        _manager->drawScene(_scene, _factory, _hlr);
    }
    catch (ErrorDrawManager_no_camera&)
    {
        // Если камера не задана — ничего не рисуем (тихо).
    }
}
