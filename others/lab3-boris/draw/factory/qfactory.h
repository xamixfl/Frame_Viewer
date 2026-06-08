#ifndef QFACTORY_H__
#define QFACTORY_H__

#include "drawer_facory.h"
#include "qdrawer.h"


class QFactory : public DrawerFactory
{
public:
    QFactory() = default;
    explicit QFactory(std::shared_ptr<QGraphicsScene> _scene, QPointer<QGraphicsView> _view);
    ~QFactory() override = default;

    std::shared_ptr<Drawer> create_drawer() override;

private:
    std::shared_ptr<QGraphicsScene> scene;
    QPointer<QGraphicsView> view;
};

#endif
