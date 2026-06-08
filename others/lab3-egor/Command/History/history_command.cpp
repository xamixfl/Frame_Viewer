#include "history_command.h"
#include "manager_solution.h"
#include "history_manager.h"

SaveStateCommand::SaveStateCommand(std::shared_ptr<HistoryManager> historyManager, int id)
	: call(historyManager, &HistoryManager::saveState), objectId(id)
{}

void SaveStateCommand::execute()
{
	((*call.first).*call.second)(objectId);
}

RestoreStateCommand::RestoreStateCommand(std::shared_ptr<HistoryManager> historyManager, int id)
: call(historyManager, &HistoryManager::getPrevState), objectId(id)
{}

void RestoreStateCommand::execute()
{
	((*call.first).*call.second)(objectId);
}


