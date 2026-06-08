#include "manager/LoadManager.h"
#include "solution/Solution.h"
#include "creator/BaseCreator.h"
#include "director/BaseDirector.h"
#include "manager/SceneManager.h"
#include "manager/HistoryManager.h"

LoadManager::LoadManager(std::unique_ptr<Solution> solution) : _solution(std::move(solution)) {}

LoadManager::~LoadManager() = default;

LoadManager::ObjectPtr LoadManager::load(LoadId id, const std::string& filename) {
    auto creator  = _solution->create(static_cast<std::size_t>(id));
    auto director = creator->createDirector();
    return director->construct(filename);
}

void LoadManager::loadModel(SceneManager& sceneMgr, LoadId id, const std::string& filename) {
    sceneMgr.addObject(load(id, filename));
}

void LoadManager::loadCamera(SceneManager& sceneMgr, const std::string& filename) {
    sceneMgr.addObject(load(LoadId::Camera, filename));
}

void LoadManager::loadScene(SceneManager& sceneMgr, HistoryManager& historyMgr, const std::string& filename) {
    sceneMgr.setScene(load(LoadId::Scene, filename));
    historyMgr.clear();
}
