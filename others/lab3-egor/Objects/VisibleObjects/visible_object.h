#ifndef VISIBLE_OBJECT_H
#define VISIBLE_OBJECT_H

#include "base_object.h"

class VisibleObject: public BaseObject
{
public:
	VisibleObject() = default;;
	~VisibleObject() override = default;

	virtual bool isVisible() const
	{ return true; };
};


#endif //VISIBLE_OBJECT_H
