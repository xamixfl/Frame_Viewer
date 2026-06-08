#include "builder/CarcasCameraBuilder.h"
#include "bridge/CarcasCamera.h"
#include "exception/Exceptions.h"

CarcasCameraBuilder::CarcasCameraBuilder(std::unique_ptr<BaseReader> reader) noexcept
    : BaseBuilder(std::move(reader)) {}

CarcasCameraBuilder::~CarcasCameraBuilder() = default;

void CarcasCameraBuilder::build() {
    _checkReader();
    _readPosition();
    _readDirection();
    _readUp();
    _assembleResult();
}

std::unique_ptr<CarcasCamera> CarcasCameraBuilder::getResult() noexcept {
    return std::move(_impl);
}

void CarcasCameraBuilder::_checkReader() const {
    if (!_reader || !_reader->isOpen()) {
        throw BuilderNotReadyError(__FILE__, "CarcasCameraBuilder", __FUNCTION__);
    }
}

void CarcasCameraBuilder::_readPosition() {
    const double x = _reader->read();
    const double y = _reader->read();
    const double z = _reader->read();
    _position = Point(x, y, z);
}

void CarcasCameraBuilder::_readDirection() {
    const double x = _reader->read();
    const double y = _reader->read();
    const double z = _reader->read();
    _direction = Point(x, y, z);
}

void CarcasCameraBuilder::_readUp() {
    const double x = _reader->read();
    const double y = _reader->read();
    const double z = _reader->read();
    _up = Point(x, y, z);
}

void CarcasCameraBuilder::_assembleResult() {
    _impl = std::make_unique<CarcasCamera>(_position, _direction, _up);
}
