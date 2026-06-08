#ifndef PROJECTED_DATA_H
#define PROJECTED_DATA_H


#include <vector>
#include "point_2_d.h"
#include "edge.h"

class ProjectedData
{
public:
	ProjectedData() = default;
	ProjectedData(std::vector<Point2D> points, std::vector<Edge> edges)
		: screenPoints(std::move(points)), visibleEdges(std::move(edges))
	{}
	[[nodiscard]] bool isEmpty() const
	{
		return screenPoints.empty() || visibleEdges.empty();
	}

	[[nodiscard]] size_t getPointCount() const
	{ return screenPoints.size(); }
	[[nodiscard]] size_t getEdgeCount() const
	{ return visibleEdges.size(); }

	[[nodiscard]] std::vector<Point2D> const &getScreenPoints() const
	{ return screenPoints; };

	[[nodiscard]] std::vector<Edge> const &getVisibleEdges() const
	{ return visibleEdges; };

private:
	std::vector<Point2D> screenPoints;
	std::vector<Edge> visibleEdges;
};


#endif //PROJECTED_DATA_H
