#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include <memory>

#include "transform_action.h"
#include "base_object.h"
#include "base_manager.h"

class TransformManager: public BaseManager
{
public:
	TransformManager() = default;
	~TransformManager() override = default;

	void rotateObject(const std::shared_ptr<BaseObject>& object, double ax, double ay, double az);
	void moveObject(const std::shared_ptr<BaseObject>& object, double dx, double dy, double dz);
	void scaleObject(const std::shared_ptr<BaseObject>& object, double sx, double sy, double sz);
	void transformObject(const std::shared_ptr<BaseObject>& object, std::shared_ptr<TransformAction> action);
};


#endif //TRANSFORM_MANAGER_H
