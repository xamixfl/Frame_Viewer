#include "SetMaterialCommand.h"
#include "manager/SceneManager.h"
#include "manager/HistoryManager.h"
#include "composite/BaseObject.h"
#include "visitor/SetMaterialVisitor.h"
// #include "memento/Memento.h" // раскомментируйте, если будете добавлять Memento для отмены

#include <utility>

SetMaterialCommand::SetMaterialCommand(
    SceneManager& sceneMgr, 
    HistoryManager& historyMgr, 
    std::vector<size_t>&& ids, 
    const Material& material)
    : _sceneMgr(sceneMgr), 
      _historyMgr(historyMgr), 
      _ids(std::move(ids)), 
      _material(material) {}

void SetMaterialCommand::execute() {
    // Опционально: если требуется поддержка Undo/Redo для смены материала,
    // здесь можно создать и сохранить снимок (снэпшот) состояния объектов до их изменения.
    // Пример: auto snapshot = _sceneMgr.createSnapshots(_ids);
    // _historyMgr.push(snapshot);

    for (size_t id : _ids) {
        auto obj = _sceneMgr.getObject(id);
        if (obj) {
            auto visitor = std::make_shared<SetMaterialVisitor>(_material);
            obj->accept(visitor);
        }
    }
}

std::string SetMaterialCommand::name() const {
    return "SetMaterialCommand";
}
