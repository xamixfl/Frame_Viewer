//
// Created by nuelex on 02/06/25.
//

#ifndef COMBINER_HPP
#define COMBINER_HPP
#include <memory>

#include "../BaseObject/BaseObject.hpp"
#include "../BaseObject/Composite/CompositeObject.hpp"


class Combiner
{
public:
    Combiner();
    ~Combiner() = default;

    void addChild(const std::shared_ptr<BaseObject> &object);
    std::shared_ptr<BaseObject> getChild() { return _objects; }

private:
    std::shared_ptr<CompositeObject> _objects;
};



#endif //COMBINER_HPP
