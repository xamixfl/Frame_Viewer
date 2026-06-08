#ifndef BASEHLRSTRATEGY_HPP
#define BASEHLRSTRATEGY_HPP

#include <vector>
#include <cstddef>

#include "../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Links/Links.hpp"
#include "../BaseObject/Figure/ConcreteFigure/ConcreteFigureLP/Point/Points.hpp"
#include "../Transforms/CameraTransformer/BaseCameraTransformer.hpp"
#include "Faces.hpp"

class BaseHLRStrategy
{
public:
    BaseHLRStrategy() = default;
    virtual ~BaseHLRStrategy() = default;

    [[nodiscard]] virtual std::vector<size_t> visibleEdges(
        const Links&  links,
        const Points& points,
        const Faces&  faces,
        const std::shared_ptr<BaseCameraTransformer>& transformer) const = 0;
};

#endif //BASEHLRSTRATEGY_HPP
