#ifndef OBJECT_COMPOSITE_H
#define OBJECT_COMPOSITE_H

#include "base_object.h"

class ObjectComposite: public BaseObject
{
public:
	using ObjectContainer = std::vector<std::shared_ptr<BaseObject>>;

public:
	ObjectComposite() = default;
	explicit ObjectComposite(std::shared_ptr<BaseObject> first, ...);

	~ObjectComposite() override = default;

	void add(std::shared_ptr<BaseObject> object) override;
	void remove(const composite_iterator &it) override;

	void accept(std::shared_ptr<BaseVisitor> visitor) override;

	composite_iterator begin() override;
	composite_iterator end() override;

	bool isComposite() override;

	void restoreMemento(std::shared_ptr<ObjectMemento> memento) override;
	std::shared_ptr<ObjectMemento> createMemento() override;
protected:
	ObjectContainer container;
};


#endif //OBJECT_COMPOSITE_H
