#ifndef COMPOSITE_MEMENTO_H
#define COMPOSITE_MEMENTO_H

#include "object_memento.h"
#include <vector>
#include <memory>

class CompositeMemento: public ObjectMemento
{
public:
	explicit CompositeMemento(const TransformAction &action)
		: ObjectMemento(action)
	{};

	void addChildMemento(std::shared_ptr<ObjectMemento> childMemento);
	[[nodiscard]] const std::vector<std::shared_ptr<ObjectMemento>> &getChildMementos() const;

private:
	std::vector<std::shared_ptr<ObjectMemento>> childMementos_;
};


#endif //COMPOSITE_MEMENTO_H
