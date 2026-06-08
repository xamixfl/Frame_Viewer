#include "solution/Solution.h"
#include "exception/Exceptions.h"

Solution::Solution(std::initializer_list<std::pair<std::size_t, CreatorFactory>> list) {
    for (auto&& [id, factory] : list) {
        registrate(id, factory);
    }
}

bool Solution::registrate(std::size_t id, CreatorFactory factory) {
    return _callbacks.insert({id, factory}).second;
}

bool Solution::has(std::size_t id) const noexcept {
    return _callbacks.find(id) != _callbacks.end();
}

std::unique_ptr<BaseCreator> Solution::create(std::size_t id) {
    auto it = _callbacks.find(id);
    if (it == _callbacks.end()) {
        throw UnknownLoadIdError(id, __FILE__, "Solution", __FUNCTION__);
    }
    return it->second();
}
