#ifndef FACADE_HPP
#define FACADE_HPP

#include <memory>
#include <string>
#include <vector>

#include "../Managers/SceneManager/SceneManager.hpp"
#include "../Managers/LoadManager/LoadManager.hpp"
#include "../Managers/DrawManager/DrawManager.hpp"
#include "../Factory/ManagerFactory/ManagerFactory.hpp"
#include "../Drawer/Factory/AbstractDrawerFactory.hpp"
#include "../HLR/BaseHLRStrategy.hpp"
#include "../InternalRepresentation/FigureCommandGetInternalData.hpp"
#include "../Commands/CameraCommand/Add/CameraCommandAdd.hpp"
#include "../Commands/CameraCommand/Set/CameraSetCommand.hpp"
#include "../Commands/CameraCommand/GetActive/CameraCommandGetActive.hpp"
#include "../Commands/FigureCommand/Add/FigureCommandAdd.hpp"

class Facade final
{
public:
    Facade();
    ~Facade() = default;

    template <typename TReader>
    bool loadObject(const std::string& path)
    {
        try
        {
            auto obj = _loadManager->load<TReader>(LoadId::Figure, path);
            if (!obj) return false;

            saveSnapshot();
            FigureCommandAdd add{_sceneManager, obj};
            add.execute();
            return true;
        }
        catch (...) { return false; }
    }

    template <typename TReader>
    bool loadCamera(const std::string& path)
    {
        try
        {
            auto obj = _loadManager->load<TReader>(LoadId::Camera, path);
            if (!obj) return false;

            saveSnapshot();
            CameraCommandAdd add{_sceneManager, obj};
            add.execute();

            std::shared_ptr<BaseObject> active{nullptr};
            CameraCommandGetActive getActive{_drawManager, active};
            getActive.execute();
            if (!active)
            {
                CameraSetCommand setCmd{_drawManager, obj};
                setCmd.execute();
            }
            return true;
        }
        catch (...) { return false; }
    }

    bool loadComposite(const std::string& path);

    void deleteObjects(const std::vector<size_t>& ids);
    void deleteCameras(const std::vector<size_t>& ids);

    void moveObjects (const std::vector<size_t>& ids,
                      double dx, double dy, double dz);
    void rotateObjects(const std::vector<size_t>& ids,
                       double ox, double oy, double oz,
                       double cx, double cy, double cz);
    void scaleObjects(const std::vector<size_t>& ids,
                      double kx, double ky, double kz,
                      double cx, double cy, double cz);

    void moveCameras (const std::vector<size_t>& ids,
                      double dx, double dy, double dz);
    void rotateCameras(const std::vector<size_t>& ids,
                       double ox, double oy, double oz);

    void setActiveCamera(int id);
    void combineObjects(const std::vector<size_t>& ids);

    bool undo();
    bool redo();

    void render(const std::shared_ptr<AbstractDrawerFactory>& factory,
                const std::shared_ptr<BaseHLRStrategy>&       hlr) const;
    void clear (const std::shared_ptr<AbstractDrawerFactory>& factory) const;

    [[nodiscard]] bool getObjectInternalData(size_t id,
                                             FigureInternalData& out) const;

    [[nodiscard]] size_t objectCount() const;
    [[nodiscard]] size_t cameraCount() const;

private:
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<LoadManager>  _loadManager;
    std::shared_ptr<DrawManager>  _drawManager;

    void saveSnapshot() const;
    void createSceneManager(const ManagerFactory&);
    void createLoadManager(const ManagerFactory&);
    void createDrawManager(const ManagerFactory&);
};

#endif // FACADE_HPP
