#include "visitor/ScaleVisitor.h"
#include "bridge/BaseModelImpl.h"
#include "bridge/BaseCameraImpl.h"
#include "bridge/BaseLightImpl.h"

void ScaleVisitor::visit(BaseModelImpl& impl) noexcept {
    auto& points = impl.getPoints();
    if (points.empty()) {
        return;
    }

    double cx = 0.0, cy = 0.0, cz = 0.0;
    for (const Point& p : points) {
        cx += p.getX();
        cy += p.getY();
        cz += p.getZ();
    }
    const auto n = static_cast<double>(points.size());
    cx /= n; cy /= n; cz /= n;

    for (Point& p : points) {
        p.move(-cx, -cy, -cz);
        p.scale(_transform.getX(), _transform.getY(), _transform.getZ());
        p.move(cx, cy, cz);
    }
}

void ScaleVisitor::visit(BaseCameraImpl& /*impl*/) noexcept {}

void ScaleVisitor::visit(BaseLightImpl& impl) noexcept {
    Point pos = impl.getPosition();
    pos.scale(_transform.getX(), _transform.getY(), _transform.getZ());
    impl.setPosition(pos);
}
