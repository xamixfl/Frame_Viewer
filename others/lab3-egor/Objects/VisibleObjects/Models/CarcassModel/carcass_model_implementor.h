#ifndef CARCASS_MODEL_IMPLEMENTOR_H
#define CARCASS_MODEL_IMPLEMENTOR_H

#include <vector>
#include <memory>
#include "edge.h"
#include "point.h"
#include "transform_action.h"
#include "face.h"

class CarcassModelImplementor
{
public:
	virtual ~CarcassModelImplementor() = default;

	CarcassModelImplementor() = default;
	CarcassModelImplementor(const CarcassModelImplementor &other) = delete;
	CarcassModelImplementor(CarcassModelImplementor &&other) = delete;

//	virtual void transform(std::shared_ptr<TransformAction> action) = 0;
	[[nodiscard]] virtual std::vector<Edge> getEdges() const = 0;
	[[nodiscard]] virtual std::vector<Point> getPoints() const = 0;
	[[nodiscard]] virtual std::vector<Face> getFaces() const = 0;

	virtual void addPoint(const Point &point) = 0;
	virtual void addEdge(const Edge &edge) = 0;
	virtual void addFace(const Face &face) = 0;

	virtual Point getCenter() const = 0;
	virtual void setCenter(const Point &center) = 0;

	virtual void linkEdgesAndFaces() = 0;
	[[nodiscard]] virtual std::vector<size_t> getAdjacentFacesForEdge(const Edge& edge) const = 0;
};


#endif //CARCASS_MODEL_IMPLEMENTOR_H
