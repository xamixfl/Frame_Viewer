#include "object.h"


std::size_t Object::nextid = 0;

Object::~Object() = default;


Composite::Composite(const std::shared_ptr<Object> &obj)
{
    elems.push_back(obj);
}

Composite::Composite(const std::vector<std::shared_ptr<Object>> &vec)
{
    elems = vec;
}

bool Composite::add(const std::shared_ptr<Object> &obj)
{
    elems.push_back(obj);

    return true;
}

bool Composite::remove(const iterator &it)
{
    elems.erase(it);

    return true;
}

void Composite::accept(const std::shared_ptr<BaseVisitor> &visitor)
{
    for (auto &elem : elems)
    {
        elem->accept(visitor);
    }
}

std::shared_ptr<Memento> Composite::create_snapshot()
{
    std::vector<std::shared_ptr<Memento>> states;

    for (auto &obj : elems)
    {
        states.push_back(obj->create_snapshot());
    }

    return std::shared_ptr<CompositeMemento>(new CompositeMemento(states));
}

void Composite::restore_snapshot(std::shared_ptr<Memento> snapshot)
{
    std::shared_ptr<CompositeMemento> memento = std::dynamic_pointer_cast<CompositeMemento>(snapshot);

    if (memento)
    {
        for (std::size_t i = 0; i < elems.size(); i++)
        {
            elems[i]->restore_snapshot(memento->states[i]);
        }
    }
}

Composite::iterator Composite::begin()
{
    return elems.begin();
}

Composite::iterator Composite::end()
{
    return elems.end();
}
