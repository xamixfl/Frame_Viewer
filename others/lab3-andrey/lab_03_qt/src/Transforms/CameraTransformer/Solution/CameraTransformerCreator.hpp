//
// Created by nuelex on 21/05/25.
//

#ifndef CAMERATRANSFORMERCREATOR_HPP
#define CAMERATRANSFORMERCREATOR_HPP
#include <memory>

#include "../BaseCameraTransformer.hpp"


class CameraTransformerCreator
{
public:
    CameraTransformerCreator() = default;
    virtual ~CameraTransformerCreator() = default;

    [[nodiscard]] virtual std::shared_ptr<BaseCameraTransformer> createCameraTransformer(const std::shared_ptr<Camera> &camera) const = 0;
};

template <typename T>
requires std::is_base_of_v<BaseCameraTransformer, T> && (! std::is_abstract_v<T>)
class ConcreteCameraTransformerCreator : public CameraTransformerCreator
{
public:
    ConcreteCameraTransformerCreator() = default;
    ~ConcreteCameraTransformerCreator() override = default;

    [[nodiscard]] std::shared_ptr<BaseCameraTransformer> createCameraTransformer(const std::shared_ptr<Camera> &camera) const override
    {
        return std::make_shared<T>(camera);
    }
};



#endif //CAMERATRANSFORMERCREATOR_HPP
