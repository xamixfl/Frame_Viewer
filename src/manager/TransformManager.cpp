#include "manager/TransformManager.h"

#include <memory>

#include "composite/BaseObject.h"
#include "composite/CompositeObject.h"
#include "data/Transform.h"
#include "manager/HistoryManager.h"
#include "manager/SceneManager.h"
#include "visitor/MoveVisitor.h"
#include "visitor/RotateVisitor.h"
#include "visitor/ScaleVisitor.h"

namespace {

std::shared_ptr<CompositeObject> buildGroup(SceneManager& sceneMgr,
                                            const std::vector<size_t>& ids) {
    auto group = std::make_shared<CompositeObject>();
    for (size_t id : ids) {
        group->add(sceneMgr.getObject(id));
    }
    return group;
}

} // namespace

void TransformManager::move(BaseObject& obj, const Transform& t) {
    auto visitor = std::make_shared<MoveVisitor>(t);
    obj.accept(visitor);
}

void TransformManager::rotate(BaseObject& obj, const Transform& t) {
    auto visitor = std::make_shared<RotateVisitor>(t);
    obj.accept(visitor);
}

void TransformManager::scale(BaseObject& obj, const Transform& t) {
    auto visitor = std::make_shared<ScaleVisitor>(t);
    obj.accept(visitor);
}

void TransformManager::moveGroup(SceneManager& sceneMgr, HistoryManager& historyMgr,
                                 const std::vector<size_t>& ids, const Transform& t,
                                 const std::string& opName) {
    if (ids.empty()) {
        return;
    }
    auto group = buildGroup(sceneMgr, ids);
    historyMgr.save(group, opName);
    move(*group, t);
}

void TransformManager::rotateGroup(SceneManager& sceneMgr, HistoryManager& historyMgr,
                                   const std::vector<size_t>& ids, const Transform& t,
                                   const std::string& opName) {
    if (ids.empty()) {
        return;
    }
    auto group = buildGroup(sceneMgr, ids);
    historyMgr.save(group, opName);
    rotate(*group, t);
}

void TransformManager::scaleGroup(SceneManager& sceneMgr, HistoryManager& historyMgr,
                                  const std::vector<size_t>& ids, const Transform& t,
                                  const std::string& opName) {
    if (ids.empty()) {
        return;
    }
    auto group = buildGroup(sceneMgr, ids);
    historyMgr.save(group, opName);
    scale(*group, t);
}
