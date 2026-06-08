//
// Created by nuelex on 20/05/25.
//

#ifndef DRAWVISITORHASH_HPP
#define DRAWVISITORHASH_HPP
#include <cstddef>
#include <memory>

#include "../../../BaseObject/BaseObject.hpp"

class DrawVisitorHash
{
public:
    DrawVisitorHash() = default;
    ~DrawVisitorHash() = default;

    std::size_t operator()(const std::shared_ptr<BaseObject> &object) const
    {
        return typeid(*object).hash_code();
    }
};

class DrawVisitorEqual
{
public:
    DrawVisitorEqual() = default;
    ~DrawVisitorEqual() = default;

    std::size_t operator()(const std::shared_ptr<BaseObject> &object1, const std::shared_ptr<BaseObject> &object2) const
    {
        return typeid(*object1).hash_code() == typeid(*object2).hash_code();
    }
};

#endif //DRAWVISITORHASH_HPP
