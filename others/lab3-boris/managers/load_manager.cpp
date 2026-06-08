#include "load_manager.h"


LoadManager::LoadManager(std::shared_ptr<DirectorSolution> _solution)
    : solution(std::move(_solution))
{}
