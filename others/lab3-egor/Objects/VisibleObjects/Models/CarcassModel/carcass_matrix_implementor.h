#ifndef CARCASS_MATRIX_IMPLEMENTOR_H
#define CARCASS_MATRIX_IMPLEMENTOR_H

#include <map>
#include "carcass_model_implementor.h"

class CarcassMatrixImplementor: public CarcassModelImplementor
{
public:
	CarcassMatrixImplementor();
	~CarcassMatrixImplementor() override = default;

//	virtual void transform(std::shared_ptr<TransformAction> action) override;

	virtual void addEdge(const Edge &edge) override;
	virtual void addPoint(const Point &point) override;
	virtual void addFace(const Face &face) override;

	[[nodiscard]] virtual std::vector<Point> getPoints() const override;
	[[nodiscard]] virtual std::vector<Edge> getEdges() const override;
	[[nodiscard]] std::vector<Face> getFaces() const override;

	[[nodiscard]] virtual Point getCenter() const override;
	virtual void setCenter(const Point &center) override;

	[[nodiscard]] std::vector<size_t> getAdjacentFacesForEdge(const Edge& edge) const override;
	void linkEdgesAndFaces() override;

protected:
	Point center{};

	std::vector<Point> points;
	std::vector<std::vector<bool>> adjacencyMatrix;
	std::vector<Face> faces;
	std::map<std::pair<size_t, size_t>, std::vector<size_t>> edgeFaceMap;
};


#endif //CARCASS_MATRIX_IMPLEMENTOR_H
