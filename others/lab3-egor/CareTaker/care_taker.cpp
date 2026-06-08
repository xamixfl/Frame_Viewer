#include "care_taker.h"


std::shared_ptr<ObjectMemento> CareTaker::getMemento(int objectId)
{
	auto &states = objectHistories[objectId].second;

	std::shared_ptr<ObjectMemento> lastState;

	if (!states.empty())
	{
		lastState = states.back();
		states.pop_back();
	}

	cleanExpiredObjects();

	return lastState;
}

void CareTaker::setMemento(int objectId, CareTaker::saveData &data)
{
	objectHistories[objectId].first = data.first;
	objectHistories[objectId].second.push_back(data.second);

	limitHistorySize(objectHistories[objectId]);

	cleanExpiredObjects();
}

void CareTaker::cleanExpiredObjects()
{
	std::erase_if(objectHistories,
				  [](const auto &item)
				  { return item.second.first.expired(); });
}

void CareTaker::limitHistorySize(CareTaker::MemData history)
{
	while (history.second.size() > MAX_HISTORY_SIZE)
		history.second.pop_back();
}
