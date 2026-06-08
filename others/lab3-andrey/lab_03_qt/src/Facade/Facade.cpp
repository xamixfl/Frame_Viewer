#include "Facade.hpp"

#include "../Commands/CameraCommand/Remove/CameraRemoveCommand.hpp"
#include "../Commands/CameraCommand/GetById/CameraCommandGetById.hpp"
#include "../Commands/FigureCommand/Remove/FigureRemoveCommand.hpp"
#include "../Commands/FigureCommand/GetByID/FigureCommandGetById.hpp"
#include "../Commands/DrawCommand/DrawCommand.hpp"
#include "../Commands/DrawCommand/CleanCommand.hpp"
#include "../Commands/TransformCommand/TransformCommand.hpp"
#include "../Visitors/Transform/Move/MoveObjectVisitor.hpp"
#include "../Visitors/Transform/Rotate/RotateObjectVisitor.hpp"
#include "../Visitors/Transform/Scale/ScaleObjectVisitor.hpp"
#include "../BaseObject/Composite/CompositeObject.hpp"
#include "../Builders/Moderators/Moderators/Composite/CompositeLoader.hpp"

Facade::Facade()
{
    ManagerFactory factory;
    createSceneManager(factory);
    createLoadManager(factory);
    createDrawManager(factory);
}

void Facade::createSceneManager(const ManagerFactory& f) { _sceneManager = f.createSceneManager(); }
void Facade::createLoadManager(const ManagerFactory& f)  { _loadManager  = f.createLoadManager(); }
void Facade::createDrawManager(const ManagerFactory& f)  { _drawManager  = f.createDrawManager(); }

void Facade::saveSnapshot() const { _sceneManager->saveSnapshot(); }

bool Facade::loadComposite(const std::string& path)
{
    try
    {
        CompositeLoader loader{_loadManager};
        auto obj = loader.load(path);
        if (!obj) return false;

        saveSnapshot();
        FigureCommandAdd add{_sceneManager, obj};
        add.execute();
        return true;
    }
    catch (...) { return false; }
}

void Facade::deleteObjects(const std::vector<size_t>& ids)
{
    if (ids.empty()) return;
    saveSnapshot();
    auto sorted = ids;
    std::sort(sorted.begin(), sorted.end(), std::greater<>{});
    for (size_t id : sorted)
    {
        try { FigureRemoveCommand cmd{_sceneManager, id}; cmd.execute(); }
        catch (...) {}
    }
}

void Facade::deleteCameras(const std::vector<size_t>& ids)
{
    if (ids.empty()) return;
    saveSnapshot();
    auto sorted = ids;
    std::sort(sorted.begin(), sorted.end(), std::greater<>{});
    for (size_t id : sorted)
    {
        try { CameraRemoveCommand cmd{_sceneManager, id}; cmd.execute(); }
        catch (...) {}
    }
}

void Facade::moveObjects(const std::vector<size_t>& ids, double dx, double dy, double dz)
{
    if (ids.empty()) return;
    saveSnapshot();
    auto transform = std::make_shared<Mover>(dx, dy, dz, Point{});
    for (size_t id : ids)
    {
        try
        {
            std::shared_ptr<BaseObject> obj{nullptr};
            FigureCommandGetById get{_sceneManager, obj, id};
            get.execute();
            if (!obj) continue;
            TransformCommand<MoveObjectVisitor> cmd{obj, transform};
            cmd.execute();
        }
        catch (...) {}
    }
}

void Facade::rotateObjects(const std::vector<size_t>& ids,
                           double ox, double oy, double oz,
                           double cx, double cy, double cz)
{
    if (ids.empty()) return;
    saveSnapshot();
    auto transform = std::make_shared<Rotater>(ox, oy, oz, Point{cx, cy, cz});
    for (size_t id : ids)
    {
        try
        {
            std::shared_ptr<BaseObject> obj{nullptr};
            FigureCommandGetById get{_sceneManager, obj, id};
            get.execute();
            if (!obj) continue;
            TransformCommand<RotateObjectVisitor> cmd{obj, transform};
            cmd.execute();
        }
        catch (...) {}
    }
}

void Facade::scaleObjects(const std::vector<size_t>& ids,
                          double kx, double ky, double kz,
                          double cx, double cy, double cz)
{
    if (ids.empty()) return;
    saveSnapshot();
    auto transform = std::make_shared<Scaler>(kx, ky, kz, Point{cx, cy, cz});
    for (size_t id : ids)
    {
        try
        {
            std::shared_ptr<BaseObject> obj{nullptr};
            FigureCommandGetById get{_sceneManager, obj, id};
            get.execute();
            if (!obj) continue;
            TransformCommand<ScaleObjectVisitor> cmd{obj, transform};
            cmd.execute();
        }
        catch (...) {}
    }
}

void Facade::moveCameras(const std::vector<size_t>& ids, double dx, double dy, double dz)
{
    if (ids.empty()) return;
    saveSnapshot();
    auto transform = std::make_shared<Mover>(dx, dy, dz, Point{});
    for (size_t id : ids)
    {
        try
        {
            std::shared_ptr<BaseObject> cam{nullptr};
            CameraCommandGetById get{_sceneManager, cam, id};
            get.execute();
            if (!cam) continue;
            TransformCommand<MoveObjectVisitor> cmd{cam, transform};
            cmd.execute();
        }
        catch (...) {}
    }
}

void Facade::rotateCameras(const std::vector<size_t>& ids, double ox, double oy, double oz)
{
    if (ids.empty()) return;
    saveSnapshot();
    auto transform = std::make_shared<Rotater>(ox, oy, oz, Point{});
    for (size_t id : ids)
    {
        try
        {
            std::shared_ptr<BaseObject> cam{nullptr};
            CameraCommandGetById get{_sceneManager, cam, id};
            get.execute();
            if (!cam) continue;
            TransformCommand<RotateObjectVisitor> cmd{cam, transform};
            cmd.execute();
        }
        catch (...) {}
    }
}

void Facade::setActiveCamera(int id)
{
    if (id < 0)
    {
        CameraSetCommand cmd{_drawManager, nullptr};
        cmd.execute();
        return;
    }
    try
    {
        std::shared_ptr<BaseObject> cam{nullptr};
        CameraCommandGetById getCmd{_sceneManager, cam, static_cast<size_t>(id)};
        getCmd.execute();
        if (!cam) return;
        CameraSetCommand setCmd{_drawManager, cam};
        setCmd.execute();
    }
    catch (...) {}
}

void Facade::combineObjects(const std::vector<size_t>& ids)
{
    if (ids.size() < 2) return;
    saveSnapshot();

    auto composite = std::make_shared<CompositeObject>();
    for (size_t id : ids)
    {
        try
        {
            std::shared_ptr<BaseObject> obj{nullptr};
            FigureCommandGetById getCmd{_sceneManager, obj, id};
            getCmd.execute();
            if (obj) composite->addChild(obj);
        }
        catch (...) {}
    }

    auto sorted = ids;
    std::sort(sorted.begin(), sorted.end(), std::greater<>{});
    for (size_t id : sorted)
    {
        try { FigureRemoveCommand rm{_sceneManager, id}; rm.execute(); }
        catch (...) {}
    }

    FigureCommandAdd add{_sceneManager, composite};
    add.execute();
}

bool Facade::undo() { return _sceneManager->undo(); }
bool Facade::redo() { return _sceneManager->redo(); }

void Facade::render(const std::shared_ptr<AbstractDrawerFactory>& factory,
                    const std::shared_ptr<BaseHLRStrategy>&       hlr) const
{
    try
    {
        CleanCommand clean{_drawManager, factory};
        clean.execute();
        DrawCommand draw{_drawManager, _sceneManager->getScene(), factory, hlr};
        draw.execute();
    }
    catch (...) {}
}

void Facade::clear(const std::shared_ptr<AbstractDrawerFactory>& factory) const
{
    try
    {
        CleanCommand clean{_drawManager, factory};
        clean.execute();
    }
    catch (...) {}
}

bool Facade::getObjectInternalData(size_t id, FigureInternalData& out) const
{
    try
    {
        FigureCommandGetInternalData cmd{_sceneManager, id, out};
        cmd.execute();
        return true;
    }
    catch (...) { return false; }
}

size_t Facade::objectCount() const { return _sceneManager->objectsSize(); }
size_t Facade::cameraCount() const { return _sceneManager->camerasSize(); }
