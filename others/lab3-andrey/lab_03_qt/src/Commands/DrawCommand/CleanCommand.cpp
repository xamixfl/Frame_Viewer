//
// Created by nuelex on 23/05/25.
//

#include "CleanCommand.hpp"

void CleanCommand::execute()
{
    _manager->clear(_factory);
}
