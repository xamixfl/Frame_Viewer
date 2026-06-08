#include "bridge/VectorCompositeImpl.h"
#include "composite/BaseObject.h"

bool VectorCompositeImpl::add(const ObjectPtr& obj) noexcept {
    if (!obj) {
        return false;
    }
    _children.push_back(obj);
    return true;
}

bool VectorCompositeImpl::remove(Iterator it) noexcept {
    if (it == _children.end()) {
        return false;
    }
    _children.erase(it);
    return true;
}
