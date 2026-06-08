#ifndef CAMERAPTUDIRECTOR_HPP
#define CAMERAPTUDIRECTOR_HPP
#include <memory>

#include "../Base/BaseDirector.hpp"
#include "../../Builders/CameraPTUBuilder/CameraPTUBuilder.hpp"


class CameraPTUDirector final : public BaseDirector
{
public:
    explicit CameraPTUDirector(std::shared_ptr<CameraPTUBuilder> builder) noexcept;
    ~CameraPTUDirector() override = default;

    [[nodiscard]] std::shared_ptr<BaseObject> create() override;

private:
    std::shared_ptr<CameraPTUBuilder> _builder;
};



#endif //CAMERAPTUDIRECTOR_HPP
