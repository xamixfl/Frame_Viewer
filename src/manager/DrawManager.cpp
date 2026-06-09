#include "manager/DrawManager.h"
#include "visitor/DrawVisitor.h"
#include "composite/BaseObject.h"
#include "composite/CompositeObject.h"
#include "manager/SceneManager.h"

DrawManager::DrawManager(AbstractDrawerFactory& factory) noexcept : _factory(factory) {}

void DrawManager::draw(BaseObject& obj, std::shared_ptr<DrawVisitor> visitor) {
    obj.accept(visitor);
}

void DrawManager::drawScene(SceneManager& sceneMgr) {
    auto visitor = std::make_shared<DrawVisitor>(_factory, sceneMgr.getActiveCamera());

    for (auto& obj : sceneMgr.getScene()) {
        obj->accept(visitor);
    }

    auto visible = sceneMgr.buildVisibleComposite();

    draw(*visible, visitor); 
}
