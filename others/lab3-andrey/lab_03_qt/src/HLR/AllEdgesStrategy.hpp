#ifndef ALLEDGESSTRATEGY_HPP
#define ALLEDGESSTRATEGY_HPP

#include "BaseHLRStrategy.hpp"

class AllEdgesStrategy : public BaseHLRStrategy
{
public:
    AllEdgesStrategy() = default;
    ~AllEdgesStrategy() override = default;

    [[nodiscard]] std::vector<size_t> visibleEdges(
        const Links&  links,
        const Points&,
        const Faces& ,
        const std::shared_ptr<BaseCameraTransformer>& ) const override
    {
        std::vector<size_t> result;
        result.reserve(links.size());
        for (size_t i = 0; i < links.size(); ++i)
            result.push_back(i);
        return result;
    }
};

#endif //ALLEDGESSTRATEGY_HPP
