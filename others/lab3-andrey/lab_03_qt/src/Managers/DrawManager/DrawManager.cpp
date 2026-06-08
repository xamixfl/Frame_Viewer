#include "DrawManager.hpp"

#include "../../Exceptions/Drawer/DrawerException.hpp"
#include "../../Exceptions/Managers/DrawManagerException.hpp"
#include "../../Transforms/CameraTransformer/Solution/CameraTransformerSolution.hpp"
#include "../../Visitors/Draw/Solution/DrawVisitorSolution.hpp"

void DrawManager::clear(const std::shared_ptr<AbstractDrawerFactory>& factory) const
{
    if (!factory)
    {
        const time_t t = time(nullptr);
        throw ErrorDrawManager_invalid_drawer(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    factory->createDrawer()->clear();
}

void DrawManager::drawScene(const std::shared_ptr<Scene>&                 scene,
                             const std::shared_ptr<AbstractDrawerFactory>& factory,
                             const std::shared_ptr<BaseHLRStrategy>&       hlr) const
{
    if (!factory)
    {
        const time_t t = time(nullptr);
        throw ErrorDrawManager_invalid_drawer(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    if (!_camera)
    {
        const time_t t = time(nullptr);
        throw ErrorDrawManager_no_camera(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }

    DrawVisitorSolution       solutionDraw{};
    CameraTransformerSolution solutionTransformer{};

    try
    {
        for (auto it = scene->objectsBegin(); it != scene->objectsEnd(); ++it)
        {
            (*it)->accept(*solutionDraw.createDrawTemplateVisitor(
                *it,
                solutionTransformer.createCameraTransformer(_camera),
                factory,
                hlr));
        }
    }
    catch (...)
    {
        const time_t t = time(nullptr);
        throw ErrorDrawManager_invalid_draw(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
}

void DrawManager::setCamera(const std::shared_ptr<BaseObject>& camera)
{
    if (!camera) { _camera = nullptr; return; }

    const auto cam = std::dynamic_pointer_cast<Camera>(camera);
    if (!cam)
    {
        const time_t t = time(nullptr);
        throw ErrorDrawManager_invalid_camera(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    _camera = cam;
}
