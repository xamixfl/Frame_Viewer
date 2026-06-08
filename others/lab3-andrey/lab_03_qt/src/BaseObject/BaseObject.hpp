//
// Created by nuelex on 10/05/25.
//

#ifndef BASEOBJECT_HPP
#define BASEOBJECT_HPP
#include <memory>
#include <vector>
#include <iterator>

#include "../Transforms/Transforms.hpp"
#include "../Visitors/BaseDrawTemplateVisitor.hpp"
#include "../Visitors/Transform/BaseTransformVisitor.hpp"


class BaseObject
{
    friend class BaseDrawTemplateVisitor;

public:
    using value_type = BaseObject;
    using size_type = size_t;
    using iterator = std::vector<std::shared_ptr<value_type>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<value_type>>::const_iterator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using shared_ptr_type = std::shared_ptr<value_type>;

    BaseObject() = default;
    BaseObject(const BaseObject&) = default;
    virtual ~BaseObject() = default;

    virtual bool CompositeCheck() { return false; }
    virtual bool VisibilityCheck() = 0;

    virtual bool addChild(const std::shared_ptr<BaseObject::value_type> &child) { return false; }
    virtual bool removeChild(const size_t id) { return false; }

    virtual iterator begin() { return iterator(); }
    virtual iterator end() { return iterator(); }
    virtual shared_ptr_type getObjectByID(size_type index) = 0;

    virtual void accept(const BaseDrawTemplateVisitor &visitor) = 0;
    virtual void accept(BaseTransformVisitor &visitor) = 0;
    virtual std::shared_ptr<BaseObject> clone() const = 0;
};



#endif //BASEOBJECT_HPP
