#ifndef INVISIBLE_OBJECT_H
#define INVISIBLE_OBJECT_H

#include "base_object.h"


class InvisibleObject: public BaseObject
{
public:
	InvisibleObject() = default;;
	~InvisibleObject() override = default;

	virtual bool isVisible() const {return false;};
	bool isComposite() override {return false;}
};


#endif //INVISIBLE_OBJECT_H
