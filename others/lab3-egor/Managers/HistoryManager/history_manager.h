#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include "base_manager.h"
#include "care_taker.h"

class HistoryManager: public BaseManager
{
public:
	HistoryManager() = default;
	~HistoryManager() override = default;

	void getPrevState(int objectId);
	void saveState(int objectId);

private:
	CareTaker careTaker;
};


#endif //HISTORY_MANAGER_H
