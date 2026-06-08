#ifndef OBJECT_MEMENTO_H
#define OBJECT_MEMENTO_H

#include "transform_action.h"

class ObjectMemento
{
	friend class BaseObject;
public:
	ObjectMemento() = delete;
	ObjectMemento(TransformAction action)
		: action(action)
	{};

	virtual ~ObjectMemento() = default;

private:
	void setAction(TransformAction action)
	{
		this->action = action;
	}

	TransformAction getAction()
	{
		return action;
	}

	TransformAction action;
};

#endif //OBJECT_MEMENTO_H
