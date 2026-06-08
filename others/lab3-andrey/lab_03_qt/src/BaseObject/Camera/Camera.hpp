//
// Created by nuelex on 18/05/25.
//

#ifndef CAMERA_TRANSFORM_HPP
#define CAMERA_TRANSFORM_HPP
#include "../BaseObject.hpp"
#include "../../Visitors/BaseDrawTemplateVisitor.hpp"


class Camera : public BaseObject
{
public:
    Camera() = default;
    ~Camera() override = default;

    bool CompositeCheck() override { return false; }
    bool VisibilityCheck() override { return false; }

    BaseObject::shared_ptr_type getObjectByID(size_type index) override { return nullptr; }

    void accept(const BaseDrawTemplateVisitor& visitor) override;
    void accept(BaseTransformVisitor &visitor) override {}
};



#endif //CAMERA_TRANSFORM_HPP
