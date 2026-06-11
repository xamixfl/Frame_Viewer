#include "builder/CameraBuilder.h"
#include "bridge/CameraImpl.h"
#include "exception/Exceptions.h"

CameraBuilder::CameraBuilder(std::unique_ptr<BaseReader> reader) noexcept
    : BaseBuilder(std::move(reader)) {}

CameraBuilder::~CameraBuilder() = default;

void CameraBuilder::build() {
    _checkReader();
    _readPosition();
    _readDirection();
    _readUp();
    _assembleResult();
}

std::unique_ptr<CameraImpl> CameraBuilder::getResult() noexcept {
    return std::move(_impl);
}

void CameraBuilder::_checkReader() const {
    if (!_reader || !_reader->isOpen()) {
        throw BuilderNotReadyError(__FILE__, "CameraBuilder", __FUNCTION__);
    }
}

void CameraBuilder::_readPosition() {
    const double x = _reader->read();
    const double y = _reader->read();
    const double z = _reader->read();
    _position = Point(x, y, z);
}

void CameraBuilder::_readDirection() {
    const double x = _reader->read();
    const double y = _reader->read();
    const double z = _reader->read();
    _direction = Point(x, y, z);
}

void CameraBuilder::_readUp() {
    const double x = _reader->read();
    const double y = _reader->read();
    const double z = _reader->read();
    _up = Point(x, y, z);
}

void CameraBuilder::_assembleResult() {
    _impl = std::make_unique<CameraImpl>(_position, _direction, _up);
}
