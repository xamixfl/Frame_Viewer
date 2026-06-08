#include "edge.h"

Edge::Edge(const size_t firstInd, const size_t secondInd)
{
	first = firstInd;
	second = secondInd;
}
size_t Edge::getFirst() const
{
	return first;
}

size_t Edge::getSecond() const
{
	return second;
}

void Edge::setFirst(size_t ind)
{
	first = ind;
}

void Edge::setSecond(size_t ind)
{
	second = ind;
}

void Edge::addAdjacentFace(size_t faceIndex)
{
	adjacentFaces.push_back(faceIndex);
}

const std::vector<size_t> &Edge::getAdjacentFaces() const
{
	return adjacentFaces;
}

