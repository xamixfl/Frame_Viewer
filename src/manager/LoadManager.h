#ifndef LOADMANAGER_H
#define LOADMANAGER_H

#include <memory>
#include <string>

#include "composite/BaseObject.h"
#include "manager/BaseManager.h"
#include "manager/LoadId.h"

class Solution;
class SceneManager;
class HistoryManager;

class LoadManager final : public BaseManager {
public:
    using ObjectPtr = std::shared_ptr<BaseObject>;

    explicit LoadManager(std::unique_ptr<Solution> solution);
    ~LoadManager() override;

    LoadManager(const LoadManager&) = delete;
    LoadManager& operator=(const LoadManager&) = delete;

    [[nodiscard]] ObjectPtr load(LoadId id, const std::string& filename);

    void loadModel(SceneManager& sceneMgr, LoadId id, const std::string& filename);
    void loadCamera(SceneManager& sceneMgr, const std::string& filename);
    void loadScene(SceneManager& sceneMgr, HistoryManager& historyMgr, const std::string& filename);

private:
    std::unique_ptr<Solution> _solution;
};

#endif
