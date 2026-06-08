#ifndef CARCASS_LIST_IMPLEMENTOR_H
#define CARCASS_LIST_IMPLEMENTOR_H


#include <vector>
#include <memory>
#include "point.h"
#include "edge.h"
#include "carcass_model_implementor.h"

class CarcassListImplementor: public CarcassModelImplementor
{
public:
	CarcassListImplementor();
	~CarcassListImplementor() override = default;


	virtual void addEdge(const Edge &edge) override;
	virtual void addPoint(const Point &point) override;
	void addFace(const Face &face) override;

	[[nodiscard]] virtual std::vector<Point> getPoints() const override;
	[[nodiscard]] virtual std::vector<Edge> getEdges() const override;
	[[nodiscard]] virtual std::vector<Face> getFaces() const override;

	[[nodiscard]] virtual Point getCenter() const override;
	virtual void setCenter(const Point &center) override;
	void linkEdgesAndFaces() override;
	std::vector<size_t> getAdjacentFacesForEdge(const Edge &edge) const override;

protected:
	Point center{};
	std::vector<Point> points;
	std::vector<Edge> edges;
	std::vector<Face> faces;
};


#endif //CARCASS_LIST_IMPLEMENTOR_H
