#include "carcass_list_implementor.h"
#include <algorithm>

CarcassListImplementor::CarcassListImplementor()
{
	center = Point();
	edges = std::vector<Edge>();
	points = std::vector<Point>();
	faces = std::vector<Face>();
}

void CarcassListImplementor::addEdge(const Edge &edge)
{
	edges.push_back(edge);
}

void CarcassListImplementor::addPoint(const Point &point)
{
	points.push_back(point);
}

void CarcassListImplementor::addFace(const Face &face)
{
	faces.push_back(face);
}

std::vector<Point> CarcassListImplementor::getPoints() const
{
	return points;
}

std::vector<Edge> CarcassListImplementor::getEdges() const
{
	return edges;
}

std::vector<Face> CarcassListImplementor::getFaces() const
{
	return faces;
}

Point CarcassListImplementor::getCenter() const
{
	Point copy_center(center);
	return copy_center;
}

void CarcassListImplementor::setCenter(const Point &center)
{
	this->center = center;
}

std::vector<size_t> CarcassListImplementor::getAdjacentFacesForEdge(const Edge &edge) const
{
	auto it = std::find(edges.begin(), edges.end(), edge);
	if (it != edges.end())
		return it->getAdjacentFaces();
	return {};
}

void CarcassListImplementor::linkEdgesAndFaces()
{
	for (size_t faceIdx = 0; faceIdx < faces.size(); ++faceIdx)
	{
		const auto &face = faces[faceIdx];
		const auto &indices = face.getVertexIndices();
		const size_t n = indices.size();

		for (size_t i = 0; i < n; ++i)
		{
			size_t j = (i + 1) % n;
			size_t v1 = indices[i];
			size_t v2 = indices[j];

			Edge tempEdge(v1, v2);

			auto it = std::find(edges.begin(), edges.end(), tempEdge);
			if (it != edges.end())
				it->addAdjacentFace(faceIdx);
		}
	}
}
