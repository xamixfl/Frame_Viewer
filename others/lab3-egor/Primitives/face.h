#ifndef FACE_H
#define FACE_H

#include <vector>

class Face
{
public:
	Face() = default;
	explicit Face(std::vector<size_t> indices) : vertexIndices(std::move(indices)) {}

	[[nodiscard]] const std::vector<size_t>& getVertexIndices() const { return vertexIndices; }

private:
	std::vector<size_t> vertexIndices;
};


#endif //FACE_H
