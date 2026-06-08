#include <algorithm>
#include "carcass_matrix_implementor.h"
#include "model_exception.h"

CarcassMatrixImplementor::CarcassMatrixImplementor()
	: center{}, points{}, adjacencyMatrix{}, faces{}
{}

void CarcassMatrixImplementor::addEdge(const Edge &edge)
{
	size_t index1 = edge.getFirst();
	size_t index2 = edge.getSecond();
	if (static_cast<int>(index1) < 0 || index1 >= points.size() || static_cast<int>(index2) < 0
		|| index2 >= points.size())
		throw OutOfRangeException(__FILE__, __LINE__, __func__, "Edge indices are out of range");

	adjacencyMatrix[index1][index2] = true;
	adjacencyMatrix[index2][index1] = true;
}

void CarcassMatrixImplementor::addPoint(const Point &point)
{
	points.push_back(point);

	size_t newSize = points.size();

	adjacencyMatrix.resize(newSize);

	for (auto &row : adjacencyMatrix)
		row.resize(newSize, false);
}

void CarcassMatrixImplementor::addFace(const Face &face)
{
	faces.push_back(face);
}

std::vector<Point> CarcassMatrixImplementor::getPoints() const
{
	return points;
}

std::vector<Edge> CarcassMatrixImplementor::getEdges() const
{
	std::vector<Edge> edges;

	for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
		for (size_t j = i + 1; j < adjacencyMatrix[i].size(); ++j)
			if (adjacencyMatrix[i][j])
				edges.emplace_back(i, j);

	return edges;
}

std::vector<Face> CarcassMatrixImplementor::getFaces() const
{
	return faces;
}

Point CarcassMatrixImplementor::getCenter() const
{
	Point copy(center);
	return copy;
}

void CarcassMatrixImplementor::setCenter(const Point &center)
{
	this->center = center;
}

void CarcassMatrixImplementor::linkEdgesAndFaces()
{
	edgeFaceMap.clear();

	for (size_t faceIdx = 0; faceIdx < faces.size(); ++faceIdx)
	{
		const Face &face = faces[faceIdx];
		const std::vector<size_t> &vertexIndices = face.getVertexIndices();
		const size_t vertexCount = vertexIndices.size();

		for (size_t i = 0; i < vertexCount; ++i)
		{
			size_t next = (i + 1) % vertexCount;
			size_t v1 = vertexIndices[i];
			size_t v2 = vertexIndices[next];

			size_t minIdx = std::min(v1, v2);
			size_t maxIdx = std::max(v1, v2);

			if (minIdx < adjacencyMatrix.size() &&
				maxIdx < adjacencyMatrix[minIdx].size() &&
				adjacencyMatrix[minIdx][maxIdx])
				edgeFaceMap[{minIdx, maxIdx}].push_back(faceIdx);
		}
	}
}

std::vector<size_t> CarcassMatrixImplementor::getAdjacentFacesForEdge(const Edge &edge) const
{
	size_t v1 = edge.getFirst();
	size_t v2 = edge.getSecond();

	size_t minIdx = std::min(v1, v2);
	size_t maxIdx = std::max(v1, v2);

	auto it = edgeFaceMap.find({minIdx, maxIdx});
	if (it != edgeFaceMap.end())
		return it->second;

	return {};
}
