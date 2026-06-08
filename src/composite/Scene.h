#ifndef SCENE_H
#define SCENE_H

#include <cstddef>
#include <memory>
#include <vector>

class BaseObject;

class Scene {
public:
    using ObjectPtr = std::shared_ptr<BaseObject>;
    using ObjectList = std::vector<ObjectPtr>;
    using iterator = ObjectList::iterator;
    using const_iterator = ObjectList::const_iterator;

    Scene() = default;

    void addObject(const ObjectPtr& obj);
    void removeObject(iterator it);
    void clear() noexcept;

    [[nodiscard]] iterator begin() noexcept;
    [[nodiscard]] iterator end() noexcept;
    [[nodiscard]] const_iterator begin() const noexcept;
    [[nodiscard]] const_iterator end() const noexcept;

    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

private:
    ObjectList _objects;
};

#endif // SCENE_H
