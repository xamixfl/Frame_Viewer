#ifndef CARCASCAMERABUILDER_H
#define CARCASCAMERABUILDER_H

#include <memory>
#include "builder/BaseBuilder.h"
#include "data/Point.h"

class CarcasCamera;

class CarcasCameraBuilder final : public BaseBuilder {
public:
    explicit CarcasCameraBuilder(std::unique_ptr<BaseReader> reader) noexcept;
    ~CarcasCameraBuilder() override;

    void build() override;

    [[nodiscard]] std::unique_ptr<CarcasCamera> getResult() noexcept;

private:
    Point _position;
    Point _direction;
    Point _up;
    std::unique_ptr<CarcasCamera> _impl;

    void _checkReader() const;
    void _readPosition();
    void _readDirection();
    void _readUp();
    void _assembleResult();
};

#endif
