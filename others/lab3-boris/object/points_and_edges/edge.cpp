#include "edge.h"


Edge::Edge(int a, int b) noexcept
    : first(a), second(b)
{}

Edge::Edge(const Edge &other) noexcept
    : first(other.first), second(other.second)
{}

int Edge::get_first() const noexcept
{
    return first;
}

int Edge::get_second() const noexcept
{
    return second;
}

void Edge::set_first(int val) noexcept
{
    first = val;
}

void Edge::set_second(int val) noexcept
{
    second = val;
}
