#ifndef DRAWVISITORCREATOR_HPP
#define DRAWVISITORCREATOR_HPP

#include <memory>
#include "../../../BaseObject/BaseObject.hpp"
#include "../../../Transforms/CameraTransformer/BaseCameraTransformer.hpp"
#include "../../../Drawer/Factory/AbstractDrawerFactory.hpp"
#include "../../../HLR/BaseHLRStrategy.hpp"
#include "../../../HLR/AllEdgesStrategy.hpp"

class DrawVisitorCreator
{
public:
    DrawVisitorCreator() = default;
    virtual ~DrawVisitorCreator() = default;

    [[nodiscard]] virtual std::shared_ptr<BaseDrawTemplateVisitor> createDrawVisitor(
        const std::shared_ptr<BaseCameraTransformer>& transformer,
        const std::shared_ptr<AbstractDrawerFactory>& factory,
        const std::shared_ptr<BaseHLRStrategy>&       hlr) const = 0;
};

template <typename T>
requires std::is_base_of_v<BaseDrawTemplateVisitor, T> && (!std::is_abstract_v<T>)
class ConcreteDrawVisitorCreator : public DrawVisitorCreator
{
public:
    [[nodiscard]] std::shared_ptr<BaseDrawTemplateVisitor> createDrawVisitor(
        const std::shared_ptr<BaseCameraTransformer>& transformer,
        const std::shared_ptr<AbstractDrawerFactory>& factory,
        const std::shared_ptr<BaseHLRStrategy>&       hlr) const override
    {
        return std::make_shared<T>(transformer, factory, hlr);
    }
};

#endif //DRAWVISITORCREATOR_HPP
