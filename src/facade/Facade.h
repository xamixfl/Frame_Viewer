#ifndef FACADE_H
#define FACADE_H

#include <memory>

class LoadManager;
class SceneManager;
class TransformManager;
class DrawManager;
class HistoryManager;
class BaseCommand;

class Facade final {
public:
    Facade(std::unique_ptr<LoadManager> loadMgr,
           std::unique_ptr<SceneManager> sceneMgr,
           std::unique_ptr<TransformManager> transformMgr,
           std::unique_ptr<DrawManager> drawMgr,
           std::unique_ptr<HistoryManager> historyMgr) noexcept;
    ~Facade();

    Facade(const Facade&) = delete;
    Facade& operator=(const Facade&) = delete;

    void execute(std::unique_ptr<BaseCommand> cmd);

    [[nodiscard]] LoadManager& getLoadManager() const noexcept { return *_loadMgr; }
    [[nodiscard]] SceneManager& getSceneManager() const noexcept { return *_sceneMgr; }
    [[nodiscard]] TransformManager& getTransformManager() const noexcept { return *_transformMgr; }
    [[nodiscard]] DrawManager& getDrawManager() const noexcept { return *_drawMgr; }
    [[nodiscard]] HistoryManager& getHistoryManager() const noexcept { return *_historyMgr; }

private:
    std::unique_ptr<LoadManager> _loadMgr;
    std::unique_ptr<SceneManager> _sceneMgr;
    std::unique_ptr<TransformManager> _transformMgr;
    std::unique_ptr<DrawManager> _drawMgr;
    std::unique_ptr<HistoryManager> _historyMgr;
};

#endif
