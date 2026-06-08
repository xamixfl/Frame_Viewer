#include <iostream>
#include "camera_manager.h"
#include "manager_solution.h"
#include "scene_manager.h"
#include "model_exception.h"
#include "transform_manager.h"

std::shared_ptr<Camera> CameraManager::getActiveCamera()
{
	return activeCamera;
}

void CameraManager::setActiveCamera(int cameraId)
{
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto cameraObj = sceneManager->getObject(cameraId);

	if (!cameraObj)
		throw IndexException(__FILE__, __LINE__, __func__, "Wrong object id");

	auto camera = std::dynamic_pointer_cast<Camera>(cameraObj);
	if (!camera)
		throw WrongTypeException(__FILE__, __LINE__, __func__, "Object is not camera");

	activeCamera = camera;
}

int CameraManager::addCamera(const Point &position)
{
	auto camera = std::make_shared<Camera>(std::vector<double>{position.getX(), position.getY(), -2000});

	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto cameraId = sceneManager->addObject(camera);
	return cameraId;
}

bool CameraManager::removeCamera(int cameraId)
{
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	return sceneManager->removeObject(cameraId);
}

std::shared_ptr<Camera> CameraManager::getCamera(int cameraId) const
{
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto cameraObj = sceneManager->getObject(cameraId);

	if (!cameraObj)
		throw IndexException(__FILE__, __LINE__, __func__, "Wrong object id");

	return std::dynamic_pointer_cast<Camera>(cameraObj);
}

void CameraManager::moveCamera(int cameraId, double dx, double dy, double dz)
{
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto cameraObj = sceneManager->getObject(cameraId);
	if (!cameraObj)
		throw IndexException(__FILE__, __LINE__, __func__, "Wrong object id");

	auto transformManager = ManagerSolution::getManager<TransformManager>();
	transformManager->moveObject(cameraObj, dx, dy, dz);
}

void CameraManager::rotateCamera(int cameraId, double ax, double ay)
{
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto cameraObj = sceneManager->getObject(cameraId);
	if (!cameraObj)
		throw IndexException(__FILE__, __LINE__, __func__, "Wrong object id");

	auto transformManager = ManagerSolution::getManager<TransformManager>();

	transformManager->rotateObject(cameraObj, ax, ay, 0);
}
