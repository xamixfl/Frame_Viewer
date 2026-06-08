#include "facade/Facade.h"
#include "manager/LoadManager.h"
#include "manager/SceneManager.h"
#include "manager/TransformManager.h"
#include "manager/DrawManager.h"
#include "manager/HistoryManager.h"
#include "command/BaseCommand.h"

Facade::Facade(std::unique_ptr<LoadManager> loadMgr,
               std::unique_ptr<SceneManager> sceneMgr,
               std::unique_ptr<TransformManager> transformMgr,
               std::unique_ptr<DrawManager> drawMgr,
               std::unique_ptr<HistoryManager> historyMgr) noexcept
    : _loadMgr(std::move(loadMgr)),
      _sceneMgr(std::move(sceneMgr)),
      _transformMgr(std::move(transformMgr)),
      _drawMgr(std::move(drawMgr)),
      _historyMgr(std::move(historyMgr)) {}

Facade::~Facade() = default;

void Facade::execute(std::unique_ptr<BaseCommand> cmd) {
    if (!cmd) {
        return;
    }
    cmd->execute();
}
