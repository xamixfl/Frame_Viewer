//
// Created by nuelex on 21/05/25.
//

#ifndef CAMERATRANSFORMERHASH_HPP
#define CAMERATRANSFORMERHASH_HPP
#include <memory>

#include "../../../BaseObject/Camera/Camera.hpp"


class CameraTransformerHash
{
public:
    CameraTransformerHash() = default;
    ~CameraTransformerHash() = default;

    size_t operator()(const std::shared_ptr<Camera> &camera) const
    {
        return typeid(*camera).hash_code();
    }
};

class CameraTransformerEqual
{
public:
    CameraTransformerEqual() = default;
    ~CameraTransformerEqual() = default;

    bool operator()(const std::shared_ptr<Camera> &camera1, const std::shared_ptr<Camera> &camera2) const
    {
        return typeid(*camera1).hash_code() == typeid(*camera2).hash_code();
    }
};



#endif //CAMERATRANSFORMERHASH_HPP
