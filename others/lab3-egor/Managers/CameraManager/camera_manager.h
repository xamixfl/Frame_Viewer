#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <memory>
#include "base_manager.h"
#include "camera.h"

class CameraManager: public BaseManager
{
public:
	CameraManager() = default;
	~CameraManager() override = default;

	void setActiveCamera(int cameraId);
	[[nodiscard]] std::shared_ptr<Camera> getActiveCamera();

	int addCamera(const Point &position);
	bool removeCamera(int cameraId);

	[[nodiscard]] std::shared_ptr<Camera> getCamera(int cameraId) const;

	void moveCamera(int cameraId, double dx, double dy, double dz);
	void rotateCamera(int cameraId, double ax, double ay);

private:
	std::shared_ptr<Camera> activeCamera;
};


#endif //CAMERA_MANAGER_H
