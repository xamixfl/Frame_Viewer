#ifndef FACADE_H
#define FACADE_H

#include "../Command/command.h"
#include <memory>

class Facade
{
public:
	Facade() = default;
	~Facade() = default;

	void execute(std::shared_ptr<Command> command);
private:
};


#endif //FACADE_H
