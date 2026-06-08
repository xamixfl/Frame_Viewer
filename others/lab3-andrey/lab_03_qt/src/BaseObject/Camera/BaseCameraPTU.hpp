#ifndef BASECAMERA_HPP
#define BASECAMERA_HPP
#include "BaseCameraPTUImpl.hpp"
#include "Camera.hpp"
#include "../BaseObject.hpp"
#include "../../Transforms/Vec.hpp"


class BaseCameraPTU : public Camera
{
protected:
    std::shared_ptr<BaseCameraPTUImpl> _cameraPTU;

public:
    BaseCameraPTU() = default;
    ~BaseCameraPTU() override = default;

    std::shared_ptr<BaseCameraPTUImpl> getCameraPTU() const { return _cameraPTU; }

    bool VisibilityCheck() override { return false; }

    void accept(const BaseDrawTemplateVisitor& visitor) override {}
    void accept(BaseTransformVisitor &visitor) override {}
};



#endif //BASECAMERA_HPP
