#include "facade.h"

void Facade::execute(std::shared_ptr<Command> command)
{
	command->execute();
}
