#include "visitor/RotateVisitor.h"
#include "bridge/BaseModelImpl.h"
#include "bridge/BaseCameraImpl.h"

void RotateVisitor::visit(BaseModelImpl& impl) noexcept {
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
        p.rotate(_transform.getX(), _transform.getY(), _transform.getZ());
        p.move(cx, cy, cz);
    }
}

void RotateVisitor::visit(BaseCameraImpl& impl) noexcept {
    Point dir = impl.getDirection();
    dir.rotate(_transform.getX(), _transform.getY(), _transform.getZ());
    impl.setDirection(dir);

    Point up = impl.getUp();
    up.rotate(_transform.getX(), _transform.getY(), _transform.getZ());
    impl.setUp(up);
}
