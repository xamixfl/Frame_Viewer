#ifndef FIGUREDIRECTOR_HPP
#define FIGUREDIRECTOR_HPP
#include <memory>

#include "../Base/BaseDirector.hpp"
#include "../../Builders/FigureLPBuilder/FigureLPBuilder.hpp"


class FigureLPDirector final : public BaseDirector
{
public:
    explicit FigureLPDirector(std::shared_ptr<FigureLPBuilder> builder) noexcept;
    ~FigureLPDirector() override = default;

    [[nodiscard]] std::shared_ptr<BaseObject> create() override;

private:
    std::shared_ptr<FigureLPBuilder> _builder;
};



#endif //FIGUREDIRECTOR_HPP
