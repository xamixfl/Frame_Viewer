#ifndef SCENE_H
#define SCENE_H

#include "base_object.h"
#include <unordered_map>

using ObjectMap = std::unordered_map<int, std::shared_ptr<BaseObject>>;
using Iterator = ObjectMap::iterator;

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	int addObject(const std::shared_ptr<BaseObject> &obj);
	bool removeObject(int id);
	std::shared_ptr<BaseObject> getObject(int id);

	Iterator begin();
	Iterator end();

private:
	ObjectMap objects;
	int objectCount = 0;
};


#endif //SCENE_H
