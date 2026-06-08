#include "history_manager.h"
#include "scene_manager.h"
#include "manager_solution.h"

void HistoryManager::getPrevState(int objectId)
{
	auto memento = careTaker.getMemento(objectId);

	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto object = sceneManager->getObject(objectId);

	auto action = CareTaker::saveData(object, object->createMemento());

	object->restoreMemento(memento);
}

void HistoryManager::saveState(int objectId)
{
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto object = sceneManager->getObject(objectId);

	auto action = CareTaker::saveData(object, object->createMemento());

	careTaker.setMemento(objectId, action);
}