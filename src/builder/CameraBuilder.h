#ifndef CameraBuiler_H
#define CameraBuiler_H

#include <memory>
#include "builder/BaseBuilder.h"
#include "data/Point.h"

class CameraImpl;

class CameraBuiler final : public BaseBuilder {
public:
    explicit CameraBuiler(std::unique_ptr<BaseReader> reader) noexcept;
    ~CameraBuiler() override;

    void build() override;

    [[nodiscard]] std::unique_ptr<CameraImpl> getResult() noexcept;

private:
    Point _position;
    Point _direction;
    Point _up;
    std::unique_ptr<CameraImpl> _impl;

    void _checkReader() const;
    void _readPosition();
    void _readDirection();
    void _readUp();
    void _assembleResult();
};

#endif
