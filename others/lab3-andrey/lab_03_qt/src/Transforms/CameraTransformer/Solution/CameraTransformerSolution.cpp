//
// Created by nuelex on 21/05/25.
//

#include "CameraTransformerSolution.hpp"

#include "../../../BaseObject/Camera/CameraPTU.hpp"
#include "../../../Exceptions/transform/TransformerException.hpp"
#include "../CameraPTU/CameraPTUTransformer.hpp"

void CameraTransformerSolution::reg(const std::shared_ptr<Camera>& camera, const std::shared_ptr<CameraTransformerCreator>& creator)
{
    _creators[camera] = creator;
}

CameraTransformerSolution::CameraTransformerSolution()
{
    try
    {
        this->reg(std::make_shared<CameraPTU>(), std::make_shared<ConcreteCameraTransformerCreator<CameraPTUTransformer>>());
    }
    catch (std::bad_alloc &e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTransformer_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}

std::shared_ptr<BaseCameraTransformer> CameraTransformerSolution::createCameraTransformer(const std::shared_ptr<Camera>& camera)
{
    const auto it = _creators.find(camera);

    if (it == _creators.end())
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTransformer_invalid_camera(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    try
    {
        return it->second->createCameraTransformer(camera);
    }
    catch (std::bad_alloc &e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTransformer_bad_alloc(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }
}



