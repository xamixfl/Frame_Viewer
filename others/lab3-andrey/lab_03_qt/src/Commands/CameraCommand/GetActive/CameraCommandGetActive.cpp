//
// Created by nuelex on 25/05/25.
//

#include "CameraCommandGetActive.hpp"

void CameraCommandGetActive::execute()
{
    _object = _manager->getCamera();
}
