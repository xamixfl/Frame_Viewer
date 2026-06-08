#ifndef QDRAWER_H__
#define QDRAWER_H__

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointer>

#include "drawer.h"
#include "point.h"


class QDrawer : public Drawer
{
public:
    QDrawer() = default;
    explicit QDrawer(std::shared_ptr<QGraphicsScene> _scene, QPointer<QGraphicsView> _view);
    ~QDrawer() override = default;

    void draw_line(const Point &first, const Point &second) override;
    void clear_scene() override;

private:
    std::shared_ptr<QGraphicsScene> scene;
    QPointer<QGraphicsView> view;
};

#endif
