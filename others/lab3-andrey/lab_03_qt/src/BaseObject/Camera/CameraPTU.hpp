//
// Created by nuelex on 10/05/25.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "BaseCameraPTU.hpp"
#include "CameraPTUImpl.hpp"
#include "../BaseObject.hpp"
#include "../../Transforms/Vec.hpp"
#include "CameraPTUImpl.hpp"

class CameraPTU : public BaseCameraPTU
{
    std::shared_ptr<BaseObject> clone() const override
    {
        auto impl = std::dynamic_pointer_cast<CameraPTUImpl>(_cameraPTU);
        auto deepImpl = impl ? std::make_shared<CameraPTUImpl>(*impl)
                             : _cameraPTU;
        return std::make_shared<CameraPTU>(deepImpl);
    }

public:
    CameraPTU() = default;
    explicit CameraPTU(const std::shared_ptr<BaseCameraPTUImpl> &cameraPTU) { _cameraPTU = cameraPTU; }
    ~CameraPTU() override = default;

    bool VisibilityCheck() override { return false; }
    bool CompositeCheck() override { return false; }

    void accept(const BaseDrawTemplateVisitor& visitor) override;
    void accept(BaseTransformVisitor &visitor) override { visitor.visit(*_cameraPTU); }
};



#endif //CAMERA_HPP
