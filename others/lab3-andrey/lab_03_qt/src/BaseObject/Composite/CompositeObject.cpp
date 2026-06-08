//
// Created by nuelex on 10/05/25.
//

#include "CompositeObject.hpp"

#include "../../Exceptions/BaseObject/CompositeException.hpp"

bool CompositeObject::addChild(const std::shared_ptr<BaseObject::value_type>& child)
{
    bool flag = true;

    try
    {
        children.push_back(child);
    }
    catch (std::bad_alloc& e)
    {
        flag = false;
    }

    return flag;
}

BaseObject::shared_ptr_type CompositeObject::getObjectByID(BaseObject::size_type index)
{
    if (index >= children.size())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorCompositeObject_out_of_range(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    return children[index];
}

void CompositeObject::accept(const BaseDrawTemplateVisitor& visitor)
{
    for (const std::shared_ptr<BaseObject>& child : children)
    {
        child->accept(visitor);
    }
}

void CompositeObject::accept(BaseTransformVisitor& visitor)
{
    for (const std::shared_ptr<BaseObject>& child : children)
    {
        child->accept(visitor);
    }
}

bool CompositeObject::removeChild(const size_t id)
{
    bool flag = true;

    if (id >= children.size())
    {
        flag = false;
    }

    if (flag)
        children.erase(children.begin() + id);

    return flag;
}



