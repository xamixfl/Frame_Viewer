#include "visitor/MoveVisitor.h"
#include "bridge/BaseModelImpl.h"
#include "bridge/BaseCameraImpl.h"

void MoveVisitor::visit(BaseModelImpl& impl) noexcept {
    for (Point& p : impl.getPoints()) {
        p.move(_transform.getX(), _transform.getY(), _transform.getZ());
    }
}

void MoveVisitor::visit(BaseCameraImpl& impl) noexcept {
    Point pos = impl.getPosition();
    pos.move(_transform.getX(), _transform.getY(), _transform.getZ());
    impl.setPosition(pos);
}

void MoveVisitor::visit(BaseLightImpl& /*impl*/) noexcept {
    // Здесь пусто. 
    // Мы оставляем комментарий, чтобы показать, что это сделано намеренно.
}
