#include "transform_manager.h"

#include <utility>
#include "transform_visitor.h"

void TransformManager::rotateObject(const std::shared_ptr<BaseObject> &object, double ax, double ay, double az)
{
	RotationData rotationData{ax, ay, az};

	TransformVisitor visitor({}, {1, 1, 1}, rotationData);
	object->accept(std::make_shared<TransformVisitor>(visitor));
}

void TransformManager::moveObject(const std::shared_ptr<BaseObject> &object, double dx, double dy, double dz)
{
	MoveData moveData{dx, dy, dz};

	TransformVisitor visitor(moveData, {1, 1, 1}, {});
	object->accept(std::make_shared<TransformVisitor>(visitor));
}

void TransformManager::scaleObject(const std::shared_ptr<BaseObject> &object, double sx, double sy, double sz)
{
	ScaleData scaleData{sx, sy, sz};

	TransformVisitor visitor({}, scaleData, {});
	object->accept(std::make_shared<TransformVisitor>(visitor));
}

void
TransformManager::transformObject(const std::shared_ptr<BaseObject> &object, std::shared_ptr<TransformAction> action)
{
	TransformVisitor visitor(std::move(action));
	object->accept(std::make_shared<TransformVisitor>(visitor));
}
