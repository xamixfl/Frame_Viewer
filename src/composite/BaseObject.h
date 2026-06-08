#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <memory>
#include <vector>

class BaseVisitor;
class BaseObject;
class Memento;

class BaseObject {
public:
    using ObjectPtr = std::shared_ptr<BaseObject>;
    using ChildrenList = std::vector<ObjectPtr>;
    using Iterator = ChildrenList::iterator;

    BaseObject() noexcept;

    virtual ~BaseObject() = default;

    BaseObject(const BaseObject&) = delete;
    BaseObject& operator=(const BaseObject&) = delete;

    [[nodiscard]] size_t getId() const noexcept { return _id; }

    [[nodiscard]] virtual bool isVisible() const noexcept = 0;
    [[nodiscard]] virtual bool isComposite() const noexcept { return false; }

    virtual void accept(const std::shared_ptr<BaseVisitor>& visitor) = 0;

    [[nodiscard]] virtual std::shared_ptr<Memento> createSnapshot() = 0;
    virtual void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) = 0;

protected:
    size_t _id;

private:
    static size_t& nextId() noexcept;
};

#endif // BASEOBJECT_H
