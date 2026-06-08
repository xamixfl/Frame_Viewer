#ifndef CAMERAPTUBUILDER_HPP
#define CAMERAPTUBUILDER_HPP
#include <memory>

#include "BaseCameraPTUBuilder.hpp"
#include "../../../BaseObject/Camera/BaseCameraPTUImpl.hpp"
#include "../../../BaseObject/Camera/CameraPTUImpl.hpp"


class CameraPTUBuilder final : public BaseCameraPTUBuilder
{
public:
    explicit CameraPTUBuilder(std::shared_ptr<BasePTUReader> reader) noexcept;
    ~CameraPTUBuilder() override = default;

    void build() override;

    [[nodiscard]] std::shared_ptr<BaseCameraPTUImpl> getResult() noexcept;

private:
    std::shared_ptr<CameraPTUImpl> _camera;

    void _checkReader() const;
    void _initCamera();
    [[nodiscard]] Point _readPoint();
    void _readPosition();
    void _readTarget();
    void _readUp();
};



#endif //CAMERAPTUBUILDER_HPP
