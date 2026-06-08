#ifndef QTDRAWERFACTORY_H
#define QTDRAWERFACTORY_H

#include <memory>
#include "factory/AbstractDrawerFactory.h"

class QGraphicsScene;

class QtDrawerFactory final : public AbstractDrawerFactory {
public:
    explicit QtDrawerFactory(QGraphicsScene& scene) noexcept : _scene(scene) {}
    ~QtDrawerFactory() override = default;

    [[nodiscard]] std::unique_ptr<BaseDrawer> createDrawer() override;

private:
    QGraphicsScene& _scene;
};

#endif // QTDRAWERFACTORY_H
