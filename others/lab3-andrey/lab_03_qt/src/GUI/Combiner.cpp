//
// Created by nuelex on 02/06/25.
//

#include "Combiner.hpp"

#include "../Exceptions/BaseObject/CompositeException.hpp"
#include "../Exceptions/GUI/CombinerException.hpp"

Combiner::Combiner()
{
    try
    {
        _objects = std::make_shared<CompositeObject>();
    }
    catch (std::bad_alloc& e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorCombiner_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

void Combiner::addChild(const std::shared_ptr<BaseObject>& object)
{
    try
    {
        _objects->addChild(object);
    }
    catch (ErrorCompositeObject_bad_alloc &e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorCombiner_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}


