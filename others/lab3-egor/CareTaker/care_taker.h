#ifndef CARE_TAKER_H
#define CARE_TAKER_H

#include <memory>
#include <vector>
#include <map>
#include <deque>
#include "base_object.h"

class ObjectMemento;

class CareTaker
{
public:
	using saveData = std::pair<std::weak_ptr<BaseObject>, std::shared_ptr<ObjectMemento>>;
	static constexpr size_t MAX_HISTORY_SIZE = 30;

	std::shared_ptr<ObjectMemento> getMemento(int objectId);
	void setMemento(int objectId, saveData &data);

private:
	using MemData = std::pair<std::weak_ptr<BaseObject>, std::deque<std::shared_ptr<ObjectMemento>>>;

	void cleanExpiredObjects();
	void limitHistorySize(MemData history);

	std::map<int, MemData> objectHistories;
};


#endif //CARE_TAKER_H
