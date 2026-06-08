#ifndef QTDRAWER_HPP
#define QTDRAWER_HPP

#include <QGraphicsScene>
#include <QPen>

#include "BaseDrawer.hpp"

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = delete;

    explicit QtDrawer(QGraphicsScene* scene, const QPen& pen = QPen(Qt::black, 1))
        : _scene(scene), _pen(pen) {}

    ~QtDrawer() override = default;

    void drawLine(const Point& p1, const Point& p2) override
    {
        _scene->addLine(
            p1.GetX(), p1.GetY(),
            p2.GetX(), p2.GetY(),
            _pen
        );
    }

    void clear() override
    {
        _scene->clear();
    }

private:
    QGraphicsScene* _scene;
    QPen            _pen;
};

#endif //QTDRAWER_HPP
