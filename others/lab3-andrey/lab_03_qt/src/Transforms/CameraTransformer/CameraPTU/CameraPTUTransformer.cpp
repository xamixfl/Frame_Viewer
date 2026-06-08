//
// Created by nuelex on 21/05/25.
//

#include "CameraPTUTransformer.hpp"

#include "../../../../consts.hpp"
#include "../../../Exceptions/transform/TransformerException.hpp"
#include "../../../Exceptions/transform/VecException.hpp"

CameraPTUTransformer::CameraPTUTransformer(const std::shared_ptr<Camera> &camera) : BaseCameraTransformer(camera)
{
    auto cameraPtr = std::dynamic_pointer_cast<CameraPTU>(camera);
    if (cameraPtr == nullptr)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTransformer_invalid_camera(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    _camera = cameraPtr;
}

Point CameraPTUTransformer::transform(const Point &other) const
{
    const auto impl = _camera->getCameraPTU();
    const Vec pos{impl->getPosition()};
    const Vec target{impl->getTarget()};
    Vec up{impl->getUp()};
    const Vec other_vec{other};

    up.normalize();

    Vec Forward = pos - target;
    try
    {
        Forward.normalize();
    }
    catch (ErrorVec_invalid_vec &e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTransformer_invalid_camera_parameters(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    Vec Right{up.vecMulConst(Forward)};
    try
    {
        Right.normalize();
    }
    catch (ErrorVec_invalid_vec &e)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTransformer_invalid_camera_parameters(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    const Vec Up{Forward.vecMulConst(Right)}; // уже normalize
    const double x_camera = (other_vec * Right) - (Right * pos);
    const double y_camera = (other_vec * Up) - (Up * pos);
    const double z_camera = (other_vec * Forward) - (Forward * pos);

    return toPerspective({x_camera, y_camera, z_camera});
}

Point CameraPTUTransformer::toPerspective(const Point& point) const
{
    if (point.GetZ() > -EPS)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorTransformer_invalid_camera_parameters(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    return {point.GetX() / fabs(point.GetZ()) * HALF_SCENE_WIDTH, \
               point.GetY() / fabs(point.GetZ()) * HALF_SCENE_HEIGHT, point.GetZ()};
}



