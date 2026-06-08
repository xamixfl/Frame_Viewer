#ifndef QTDRAWERFACTORY_HPP
#define QTDRAWERFACTORY_HPP

#include <QGraphicsScene>
#include <QPen>

#include "AbstractDrawerFactory.hpp"

class QtDrawerFactory : public AbstractDrawerFactory
{
public:
    QtDrawerFactory() = delete;

    explicit QtDrawerFactory(QGraphicsScene* scene, const QPen& pen = QPen(Qt::black, 1))
        : _scene(scene), _pen(pen) {}

    ~QtDrawerFactory() override = default;

    [[nodiscard]] std::shared_ptr<BaseDrawer> createDrawer() const override;

private:
    QGraphicsScene* _scene;
    QPen            _pen;
};

#endif //QTDRAWERFACTORY_HPP
