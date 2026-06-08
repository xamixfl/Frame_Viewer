#ifndef QTFACTORY_H
#define QTFACTORY_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "AbstractGraphicFactory.h"
#include "QtDrawer.h"

class QTFactory : public AbstractGraphicFactory
{
public:
    QTFactory();
    explicit QTFactory(std::shared_ptr<QGraphicsScene> scene, QGraphicsView* view);
    ~QTFactory() = default;

    std::shared_ptr<AbstractDrawer> get_drawer() override;

protected:
    std::shared_ptr<QGraphicsScene> scene;
    QGraphicsView* view;
};

#endif // QTFACTORY_H
