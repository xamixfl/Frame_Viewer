#ifndef COMPOSITELOADER_HPP
#define COMPOSITELOADER_HPP
#include <memory>
#include <string>

#include "../../../../BaseObject/Composite/CompositeObject.hpp"
#include "../../../../Managers/LoadManager/LoadManager.hpp"


class CompositeLoader
{
public:
    explicit CompositeLoader(std::shared_ptr<LoadManager> loader) noexcept : _loader(std::move(loader)) {}
    ~CompositeLoader() = default;

    [[nodiscard]] std::shared_ptr<BaseObject> load(const std::string& filename) const;

private:
    std::shared_ptr<LoadManager> _loader;
};



#endif //COMPOSITELOADER_HPP
