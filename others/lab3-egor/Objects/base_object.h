#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include <memory>
#include <vector>
#include "point.h"
#include "transform_action.h"
#include "object_memento.h"

class BaseVisitor;

class BaseObject
{
public:
	using composite_iterator = std::vector<std::shared_ptr<BaseObject>>::iterator;
	BaseObject();
	virtual ~BaseObject() = default;

	size_t getId();
	void setId(size_t id);

	virtual void add(std::shared_ptr<BaseObject> obj) {};
	virtual void remove(const composite_iterator &it) {};

	virtual void accept(std::shared_ptr<BaseVisitor> visitor) = 0;

	SquareMatrix<double> getPositionMatrix();
	std::shared_ptr<TransformAction> getScenePosition();

	virtual bool isComposite()
	{ return false; };
	virtual bool isVisible()
	{ return false; };

	virtual composite_iterator begin();
	virtual composite_iterator end();

	virtual void restoreMemento(std::shared_ptr<ObjectMemento> memento);
	virtual std::shared_ptr<ObjectMemento> createMemento();
protected:
	size_t id;
	std::shared_ptr<TransformAction> scenePosition;
};


#endif //BASE_OBJECT_H
