#include "object_composite.h"
#include "composite_memento.h"

ObjectComposite::ObjectComposite(std::shared_ptr<BaseObject> first, ...)
{
	for (std::shared_ptr<BaseObject> *ptr = &first; *ptr; ++ptr)
		container.push_back(*ptr);
}

void ObjectComposite::add(std::shared_ptr<BaseObject> object)
{
	container.push_back(object);
}

void ObjectComposite::remove(const BaseObject::composite_iterator &it)
{
	container.erase(it);
}

BaseObject::composite_iterator ObjectComposite::begin()
{
	return container.begin();
}

BaseObject::composite_iterator ObjectComposite::end()
{
	return container.end();
}

bool ObjectComposite::isComposite()
{
	return true;
}

void ObjectComposite::accept(std::shared_ptr<BaseVisitor> visitor)
{
	for (auto &it : container)
		it->accept(visitor);
}

std::shared_ptr<ObjectMemento> ObjectComposite::createMemento()
{
	auto compositeMemento = std::make_shared<CompositeMemento>(*scenePosition.get());

	for (auto& child : container)
	{
		if (child)
		{
			auto childMemento = child->createMemento();
			compositeMemento->addChildMemento(childMemento);
		}
	}

	return compositeMemento;

}

void ObjectComposite::restoreMemento(std::shared_ptr<ObjectMemento> memento)
{
	if (!memento) return;

	auto compositeMemento = std::dynamic_pointer_cast<CompositeMemento>(memento);

	if (compositeMemento)
	{
		BaseObject::restoreMemento(memento);

		const auto& childMementos = compositeMemento->getChildMementos();

		if (childMementos.size() == container.size())
			for (size_t i = 0; i < container.size(); ++i)
				if (container[i] && i < childMementos.size())
					container[i]->restoreMemento(childMementos[i]);
	}
	else
	{
		BaseObject::restoreMemento(memento);
	}
}
