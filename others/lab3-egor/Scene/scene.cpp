#include "scene.h"
#include <iostream>

int Scene::addObject(const std::shared_ptr<BaseObject> &obj)
{
	objects[objectCount++] = obj;

	return objectCount - 1;
}

bool Scene::removeObject(int id)
{
	return objects.erase(id) > 0;
}

std::shared_ptr<BaseObject> Scene::getObject(int id)
{
	return objects.at(id);
}

Iterator Scene::begin()
{
	return objects.begin();
}

Iterator Scene::end()
{
	return objects.end();
}

