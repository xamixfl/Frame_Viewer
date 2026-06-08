#ifndef QTDRAWER_H
#define QTDRAWER_H

#include "factory/BaseDrawer.h"

class QGraphicsScene;

class QtDrawer final : public BaseDrawer {
public:
    explicit QtDrawer(QGraphicsScene& scene, double scale = 50.0) noexcept;
    ~QtDrawer() override = default;

    void drawLine(const Point& p1, const Point& p2) override;
    void clear() override;

private:
    QGraphicsScene& _scene;
    double _scaleFactor;
};

#endif // QTDRAWER_H
