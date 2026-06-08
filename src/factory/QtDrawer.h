#ifndef QTDRAWER_H
#define QTDRAWER_H

#include "factory/BaseDrawer.h"
#include <QColor>
#include <vector>

class QGraphicsScene;
class Light;

class QtDrawer final : public BaseDrawer {
public:
    explicit QtDrawer(QGraphicsScene& scene, double scale = 50.0) noexcept;
    ~QtDrawer() override = default;

    void drawLine(const Point& p1, const Point& p2) override;
    void setColor(float r, float g, float b);
    void setLights(const std::vector<std::shared_ptr<Light>>& lights);
    void drawPolygon(const std::vector<Point>& vertices, const Material& mat);
    void clear() override;

private:
    std::vector<std::shared_ptr<Light>> _lights;
    QGraphicsScene& _scene;
    QColor _currentColor;
    double _scaleFactor;

};

#endif // QTDRAWER_H
