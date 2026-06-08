#include "scene_manager.h"
#include "object_composite.h"


SceneManager::SceneManager()
{
	scene_ = std::make_shared<Scene>();
}


std::shared_ptr<Scene> SceneManager::getScene() const
{
	return scene_;
}

void SceneManager::setScene(std::shared_ptr<Scene> scene)
{
	scene_ = scene;
}

std::shared_ptr<BaseObject> SceneManager::getObject(int objectId)
{
	return scene_->getObject(objectId);
}

bool SceneManager::removeObject(int objectId)
{
	return scene_->removeObject(objectId);
}

int SceneManager::addObject(std::shared_ptr<BaseObject> object)
{
	return scene_->addObject(object);
}

int SceneManager::makeComposite(const std::vector<int> &objectIds)
{
	auto composite = std::make_shared<ObjectComposite>();
	for (int id : objectIds)
		if (scene_->getObject(id))
		{
			composite->add(getObject(id));
			scene_->removeObject(id);
		}
	return scene_->addObject(composite);
}
