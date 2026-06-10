#ifndef VECTORCOMPOSITEIMPL_H
#define VECTORCOMPOSITEIMPL_H

#include "bridge/BaseCompositeImpl.h"

class VectorCompositeImpl final : public BaseCompositeImpl {
public:
    using ObjectPtr = BaseCompositeImpl::ObjectPtr;
    using ChildrenList = BaseCompositeImpl::ChildrenList;
    using Iterator = BaseCompositeImpl::Iterator;

    VectorCompositeImpl() = default;
    ~VectorCompositeImpl() override = default;

    VectorCompositeImpl(const VectorCompositeImpl&) = delete;
    VectorCompositeImpl& operator=(const VectorCompositeImpl&) = delete;

    Iterator begin() noexcept override { return _children.begin(); }
    Iterator end() noexcept override { return _children.end(); }

    bool add(const ObjectPtr& obj) noexcept override;
    bool remove(Iterator it) noexcept override;

private:
    ChildrenList _children;
};

#endif 
