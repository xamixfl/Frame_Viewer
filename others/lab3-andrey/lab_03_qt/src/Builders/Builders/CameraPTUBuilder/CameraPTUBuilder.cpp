#include "CameraPTUBuilder.hpp"

#include "../../../Exceptions/Builders/BuildersException.hpp"

CameraPTUBuilder::CameraPTUBuilder(std::shared_ptr<BasePTUReader> reader) noexcept
    : BaseCameraPTUBuilder(std::move(reader))
{
}

void CameraPTUBuilder::build()
{
    _checkReader();
    _initCamera();
    _readPosition();
    _readTarget();
    _readUp();
}

std::shared_ptr<BaseCameraPTUImpl> CameraPTUBuilder::getResult() noexcept
{
    return std::move(_camera);
}

void CameraPTUBuilder::_checkReader() const
{
    if (!_reader || !_reader->is_open())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorBuilder_invalid_file(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

void CameraPTUBuilder::_initCamera()
{
    try
    {
        _camera = std::make_shared<CameraPTUImpl>();
    }
    catch (std::bad_alloc&)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorBuilder_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

Point CameraPTUBuilder::_readPoint()
{
    const double x = _reader->read();
    const double y = _reader->read();
    const double z = _reader->read();
    return Point{x, y, z};
}

void CameraPTUBuilder::_readPosition()
{
    _camera->setPosition(_readPoint());
}

void CameraPTUBuilder::_readTarget()
{
    _camera->setTarget(_readPoint());
}

void CameraPTUBuilder::_readUp()
{
    _camera->setUp(_readPoint());
}
