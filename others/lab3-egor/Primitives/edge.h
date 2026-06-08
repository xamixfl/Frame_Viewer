#ifndef EDGE_H
#define EDGE_H

#include <cstddef>
#include <vector>

class Edge
{
public:
	Edge() = default;
	Edge(const size_t firstInd, const size_t secondInd);

	size_t getFirst() const;
	size_t getSecond() const;

	void setFirst(size_t ind);
	void setSecond(size_t ind);

	void addAdjacentFace(size_t faceIndex);
	[[nodiscard]] const std::vector<size_t> &getAdjacentFaces() const;

	bool operator==(const Edge &other) const
	{
		return (first == other.first && second == other.second) ||
			(first == other.second && second == other.first);
	}

private:
	size_t first, second;
	std::vector<size_t> adjacentFaces;
};


#endif //EDGE_H
