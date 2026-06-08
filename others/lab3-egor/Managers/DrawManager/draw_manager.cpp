#include <iostream>
#include "draw_manager.h"
#include "manager_solution.h"
#include "draw_visitor.h"
#include "scene_manager.h"
#include "camera_manager.h"

void DrawManager::drawScene()
{
	if (!drawer) return;

	drawer->clear();

	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto cameraManager = ManagerSolution::getManager<CameraManager>();
	auto scene = sceneManager->getScene();
	auto camera = cameraManager->getActiveCamera();

	DrawVisitor visitor(drawer, camera);
	for (auto & it : *scene)
		(*it.second).accept(std::make_shared<DrawVisitor>(visitor));
}

void DrawManager::setDrawer(std::shared_ptr<BaseDrawer> drawer_)
{
	drawer = drawer_;
}
