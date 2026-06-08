#include "manager/DrawManager.h"
#include "visitor/DrawVisitor.h"
#include "composite/BaseObject.h"
#include "composite/CompositeObject.h"
#include "manager/SceneManager.h"

DrawManager::DrawManager(AbstractDrawerFactory& factory) noexcept : _factory(factory) {}

void DrawManager::draw(BaseObject& obj, std::shared_ptr<Camera> camera) {
    auto visitor = std::make_shared<DrawVisitor>(_factory, std::move(camera));
    obj.accept(visitor);
}

void DrawManager::drawScene(SceneManager& sceneMgr) {
    auto visible = sceneMgr.buildVisibleComposite();
    draw(*visible, sceneMgr.getActiveCamera());
}
