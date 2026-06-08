#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "base_manager.h"
#include "scene.h"

class SceneManager: public BaseManager
{
public:
	SceneManager();
	~SceneManager() override = default;

	[[nodiscard]] std::shared_ptr<Scene> getScene() const;
	void setScene(std::shared_ptr<Scene> scene);

	std::shared_ptr<BaseObject> getObject(int objectId);
	bool removeObject(int objectId);
	int addObject(std::shared_ptr<BaseObject> object);
	int makeComposite(const std::vector<int>& objectIds);

private:
	std::shared_ptr<Scene> scene_;
};


#endif //SCENE_MANAGER_H
