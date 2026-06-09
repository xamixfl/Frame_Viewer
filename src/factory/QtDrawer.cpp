#include "factory/QtDrawer.h"
#include "data/Point.h"
#include "composite/Light.h"

#include <QGraphicsScene>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QColor>

QtDrawer::QtDrawer(QGraphicsScene& scene, double scale) noexcept 
    : _scene(scene), 
      _scaleFactor(scale),
      _currentColor(Qt::white) {}

void QtDrawer::drawLine(const Point& p1, const Point& p2) {
    const qreal x1 = p1.getX() * _scaleFactor;
    const qreal y1 = -p1.getY() * _scaleFactor;
    const qreal x2 = p2.getX() * _scaleFactor;
    const qreal y2 = -p2.getY() * _scaleFactor;

    QPen pen(_currentColor); 
    pen.setWidth(1);
    _scene.addLine(x1, y1, x2, y2, pen);
}

void QtDrawer::setColor(float r, float g, float b) {
    _currentColor = QColor::fromRgbF(r, g, b);
}

void QtDrawer::drawPolygon(const std::vector<Point>& vertices, const Material& mat) {
    if (vertices.size() < 3) return;

    QPainterPath path;
    path.moveTo(vertices[0].getX() * _scaleFactor, -vertices[0].getY() * _scaleFactor);
    for (size_t i = 1; i < vertices.size(); ++i) {
        path.lineTo(vertices[i].getX() * _scaleFactor, -vertices[i].getY() * _scaleFactor);
    }
    path.closeSubpath();

    QColor color = QColor::fromRgbF(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
    QBrush brush(color);

    QPen pen(Qt::black); // Обводка всегда черная для каркаса, или можешь сделать её цветом материала
    pen.setWidth(1);

    _scene.addPath(path, pen, brush);
}

void QtDrawer::setLights(const std::vector<std::shared_ptr<Light>>& lights) {
    _lights = lights;
}

void QtDrawer::clear() {
    _scene.clear();
}
