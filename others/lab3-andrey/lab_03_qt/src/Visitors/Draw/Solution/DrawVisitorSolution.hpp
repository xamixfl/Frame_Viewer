#ifndef DRAWVISITORSOLUTION_HPP
#define DRAWVISITORSOLUTION_HPP

#include <memory>
#include <unordered_map>

#include "DrawVisitorCreator.hpp"
#include "DrawVisitorHash.hpp"
#include "../../../BaseObject/BaseObject.hpp"
#include "../../../Transforms/CameraTransformer/BaseCameraTransformer.hpp"
#include "../../../Drawer/Factory/AbstractDrawerFactory.hpp"
#include "../../../HLR/BaseHLRStrategy.hpp"

class DrawVisitorSolution
{
public:
    DrawVisitorSolution();
    ~DrawVisitorSolution() = default;

    std::shared_ptr<BaseDrawTemplateVisitor> createDrawTemplateVisitor(
        const std::shared_ptr<BaseObject>&            object,
        const std::shared_ptr<BaseCameraTransformer>& transformer,
        const std::shared_ptr<AbstractDrawerFactory>& factory,
        const std::shared_ptr<BaseHLRStrategy>&       hlr);

    void reg(const std::shared_ptr<BaseObject>&       object,
             const std::shared_ptr<DrawVisitorCreator>& creator);

private:
    std::unordered_map<
        std::shared_ptr<BaseObject>,
        std::shared_ptr<DrawVisitorCreator>,
        DrawVisitorHash, DrawVisitorEqual> _creators;
};

#endif //DRAWVISITORSOLUTION_HPP
