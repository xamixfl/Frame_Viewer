#ifndef BASECOMPOSITEIMPL_H
#define BASECOMPOSITEIMPL_H

#include <memory>
#include <vector>

class BaseObject;

class BaseCompositeImpl {
public:
    using ObjectPtr = std::shared_ptr<BaseObject>;
    using ChildrenList = std::vector<ObjectPtr>;
    using Iterator = ChildrenList::iterator;

    virtual ~BaseCompositeImpl() = default;

    virtual Iterator begin() noexcept = 0;
    virtual Iterator end() noexcept = 0;

    virtual bool add(const ObjectPtr& obj) noexcept = 0;
    virtual bool remove(Iterator it) noexcept = 0;
};

#endif // BASECOMPOSITEIMPL_H
