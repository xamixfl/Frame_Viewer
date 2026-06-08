#include "camera_command.h"
#include "camera_manager.h"
#include "manager_solution.h"


AddCameraCommand::AddCameraCommand(std::shared_ptr<CameraManager> cameraManager, const Point &position)
	: call(cameraManager, &CameraManager::addCamera), position_(position)
{}

int AddCameraCommand::getCameraId() const
{
	return camera_id;
}

void AddCameraCommand::execute()
{
	camera_id = ((*call.first).*call.second)(position_);
}

SetCameraCommand::SetCameraCommand(std::shared_ptr<CameraManager> cameraManager, size_t id)
	: call(cameraManager, &CameraManager::setActiveCamera), camera_id(id)
{}

void SetCameraCommand::execute()
{
	((*call.first).*call.second)(camera_id);
}

DeleteCameraCommand::DeleteCameraCommand(std::shared_ptr<CameraManager> cameraManager, size_t id)
	: call(cameraManager, &CameraManager::removeCamera), camera_id(id)
{}

void DeleteCameraCommand::execute()
{
//	auto cameraManager = ManagerSolution::getManager<CameraManager>();
//	cameraManager->removeCamera(camera_id);
	((*call.first).*call.second)(camera_id);
}

MoveCameraCommand::MoveCameraCommand(std::shared_ptr<CameraManager> cameraManager,
									 size_t id,
									 double dx,
									 double dy,
									 double dz)
	: call(cameraManager, &CameraManager::moveCamera),
	  camera_id(id), dx(dx), dy(dy), dz(dz)
{}

void MoveCameraCommand::execute()
{
	((*call.first).*call.second)(camera_id, dx, dy, dz);
}
RotateCameraCommand::RotateCameraCommand(std::shared_ptr<CameraManager> cameraManager, size_t id, double ax, double ay)
	: call(cameraManager, &CameraManager::rotateCamera),
	  camera_id(id), ax(ax), ay(ay)
{}

void RotateCameraCommand::execute()
{
	((*call.first).*call.second)(camera_id, ax, ay);
}
