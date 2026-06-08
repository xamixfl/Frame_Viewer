#ifndef PROJECTION_ACTION_H
#define PROJECTION_ACTION_H


#include "projected_data.h"
#include "square_matrix.h"
#include "point.h"
#include "face.h"

class ProjectionAction
{
public:
	ProjectionAction() = default;

	[[nodiscard]] ProjectedData project(
		const std::vector<Point> &worldPoints,
		const std::vector<Edge> &worldEdges,
		const std::vector<Face> &worldFaces,
		const SquareMatrix<double> &mvMatrix,
		const SquareMatrix<double> &projectionMatrix,
		const std::vector<double> &viewDirection) const;

private:
	[[nodiscard]] std::vector<Point> transformToViewSpace(
		const std::vector<Point> &worldPoints,
		const SquareMatrix<double> &mvMatrix) const;

	[[nodiscard]] std::vector<Edge> determineVisibleEdges(
		const std::vector<Point> &viewSpacePoints,
		const std::vector<Edge> &worldEdges,
		const std::vector<Face> &worldFaces,
		const std::vector<double> &viewDirection) const;

	[[nodiscard]] std::vector<Point2D> projectToScreenSpace(const std::vector<Point> &viewSpacePoints,
															const SquareMatrix<double> &projectionMatrix) const;

	[[nodiscard]] Point calculateCentroid(const std::vector<Point> &points) const;

	[[nodiscard]] std::vector<std::vector<double>> buildPlaneMatrix(const std::vector<Point> &points,
																	const std::vector<Face> &faces) const;
};


#endif //PROJECTION_ACTION_H
