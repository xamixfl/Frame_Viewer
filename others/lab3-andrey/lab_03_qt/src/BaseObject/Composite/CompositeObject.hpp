//
// Created by nuelex on 10/05/25.
//

#ifndef COMPOSITEOBJECT_HPP
#define COMPOSITEOBJECT_HPP
#include "../BaseObject.hpp"


class CompositeObject : public BaseObject
{
public:
    CompositeObject() : children() {}
    CompositeObject(const CompositeObject& other) = default;
    ~CompositeObject() override = default;

    using const_child_iterator = std::vector<std::shared_ptr<value_type>>::const_iterator;
    const_child_iterator cbegin() const { return children.cbegin(); }
    const_child_iterator cend()   const { return children.cend();   }

    std::shared_ptr<BaseObject> clone() const override
    {
        auto result = std::make_shared<CompositeObject>();
        for (const auto& child : children)
            result->children.push_back(child->clone());
        return result;
    }

    bool CompositeCheck() override { return true; }
    bool VisibilityCheck() override { return false; }

    bool addChild(const std::shared_ptr<BaseObject::value_type> &child) override;
    bool removeChild(const size_t id) override;

    BaseObject::iterator begin() override { return children.begin(); }
    BaseObject::iterator end() override { return children.end(); }

    BaseObject::shared_ptr_type getObjectByID(size_type index) override;

    void accept(const BaseDrawTemplateVisitor& visitor) override;
    void accept(BaseTransformVisitor& visitor) override;

private:
    std::vector<std::shared_ptr<BaseObject::value_type>> children;
};



#endif //COMPOSITEOBJECT_HPP
