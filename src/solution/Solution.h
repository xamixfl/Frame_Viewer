#ifndef SOLUTION_H
#define SOLUTION_H

#include <cstddef>
#include <initializer_list>
#include <map>
#include <memory>
#include <utility>

#include "creator/BaseCreator.h"

class Solution {
public:
    using CreatorFactory = std::unique_ptr<BaseCreator>(*)();
    using CallbackMap = std::map<std::size_t, CreatorFactory>;

    Solution() = default;
    explicit Solution(std::initializer_list<std::pair<std::size_t, CreatorFactory>> list);
    ~Solution() = default;

    Solution(const Solution&) = delete;
    Solution& operator=(const Solution&) = delete;

    bool registrate(std::size_t id, CreatorFactory factory);
    [[nodiscard]] bool has(std::size_t id) const noexcept;

    [[nodiscard]] std::unique_ptr<BaseCreator> create(std::size_t id);

private:
    CallbackMap _callbacks;
};

#endif // SOLUTION_H
