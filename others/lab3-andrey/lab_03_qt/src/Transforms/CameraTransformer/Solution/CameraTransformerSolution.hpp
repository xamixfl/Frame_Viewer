//
// Created by nuelex on 21/05/25.
//

#ifndef CAMERATRANSFORMERSOLUTION_HPP
#define CAMERATRANSFORMERSOLUTION_HPP
#include <unordered_map>

#include "CameraTransformerCreator.hpp"
#include "CameraTransformerHash.hpp"
#include "../BaseCameraTransformer.hpp"


class CameraTransformerSolution
{
public:
    CameraTransformerSolution();
    ~CameraTransformerSolution() = default;

    std::shared_ptr<BaseCameraTransformer> createCameraTransformer(const std::shared_ptr<Camera> &camera);
    void reg(const std::shared_ptr<Camera> &camera, const std::shared_ptr<CameraTransformerCreator> &creator);

private:
    std::unordered_map<std::shared_ptr<Camera>, std::shared_ptr<CameraTransformerCreator>, \
                       CameraTransformerHash, CameraTransformerEqual> _creators;
};



#endif //CAMERATRANSFORMERSOLUTION_HPP
