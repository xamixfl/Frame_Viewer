#ifndef HISTORY_COMMAND_H
#define HISTORY_COMMAND_H

#include "command.h"
#include "history_manager.h"

class HistoryCommand: public Command
{
};

class SaveStateCommand: public HistoryCommand
{
	using Action = void (HistoryManager::*)(int id);
	using Pair = std::pair<std::shared_ptr<HistoryManager>, Action>;
public:
	SaveStateCommand(std::shared_ptr<HistoryManager> historyManager, int id);

	void execute() override;

private:
	Pair call;
	int objectId;
};

class RestoreStateCommand: public HistoryCommand
{
	using Action = void (HistoryManager::*)(int id);
	using Pair = std::pair<std::shared_ptr<HistoryManager>, Action>;
public:
	explicit RestoreStateCommand(std::shared_ptr<HistoryManager> historyManager, int id);

	void execute() override;

private:
	Pair call;
	int objectId;
};

#endif //HISTORY_COMMAND_H
