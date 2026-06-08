#include "base_object.h"


BaseObject::BaseObject()
{
	scenePosition = std::make_shared<TransformAction>();
}

size_t BaseObject::getId()
{
	return id;
}

void BaseObject::setId(size_t id)
{
	this->id = id;
}

void BaseObject::restoreMemento(std::shared_ptr<ObjectMemento> memento)
{
	if (memento)
		scenePosition = std::make_shared<TransformAction>(memento->getAction());
}

std::shared_ptr<ObjectMemento> BaseObject::createMemento()
{
	return std::make_unique<ObjectMemento>(*scenePosition);
}

BaseObject::composite_iterator BaseObject::begin()
{
	return {};
}

BaseObject::composite_iterator BaseObject::end()
{
	return {};
}


SquareMatrix<double> BaseObject::getPositionMatrix()
{
	return scenePosition->getResultMatrix();
}

std::shared_ptr<TransformAction> BaseObject::getScenePosition()
{
	return scenePosition;
}






