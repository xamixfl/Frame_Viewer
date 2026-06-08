#include "factory/QtDrawer.h"
#include "data/Point.h"

#include <QGraphicsScene>
#include <QPen>
#include <Qt>

QtDrawer::QtDrawer(QGraphicsScene& scene, double scale) noexcept : _scene(scene), _scaleFactor(scale) {}

void QtDrawer::drawLine(const Point& p1, const Point& p2) {
    const qreal x1 = p1.getX() * _scaleFactor;
    const qreal y1 = -p1.getY() * _scaleFactor;
    const qreal x2 = p2.getX() * _scaleFactor;
    const qreal y2 = -p2.getY() * _scaleFactor;

    QPen pen(Qt::red);
    pen.setWidth(1);
    _scene.addLine(x1, y1, x2, y2, pen);
}

void QtDrawer::clear() {
    _scene.clear();
}
