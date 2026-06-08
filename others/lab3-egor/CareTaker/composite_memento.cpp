#include "composite_memento.h"

void CompositeMemento::addChildMemento(std::shared_ptr<ObjectMemento> childMemento)
{
	childMementos_.push_back(childMemento);
}

const std::vector<std::shared_ptr<ObjectMemento>> &CompositeMemento::getChildMementos() const
{
	return childMementos_;
}
