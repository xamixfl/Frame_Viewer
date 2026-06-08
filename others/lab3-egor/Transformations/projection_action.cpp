#include "projection_action.h"
#include <stdexcept>
#include <cmath>

ProjectedData ProjectionAction::project(
	const std::vector<Point> &worldPoints,
	const std::vector<Edge> &worldEdges,
	const std::vector<Face> &worldFaces,
	const SquareMatrix<double> &mvMatrix,
	const SquareMatrix<double> &projectionMatrix,
	const std::vector<double> &viewDirection) const
{
	if (worldPoints.empty())
		return {};

	auto viewSpacePoints = transformToViewSpace(worldPoints, mvMatrix);

	auto visibleEdges = determineVisibleEdges(viewSpacePoints, worldEdges, worldFaces, viewDirection);

	auto screenPoints = projectToScreenSpace(viewSpacePoints, projectionMatrix);

	return ProjectedData(std::move(screenPoints), std::move(visibleEdges));
}

std::vector<Point> ProjectionAction::transformToViewSpace(
	const std::vector<Point> &worldPoints,
	const SquareMatrix<double> &mvMatrix) const
{
	std::vector<Point> viewSpacePoints;
	viewSpacePoints.reserve(worldPoints.size());

	for (const auto &point : worldPoints)
	{
		std::vector<double> homogeneous = {
			point.getX(),
			point.getY(),
			point.getZ(),
			1.0
		};

		auto transformed = mvMatrix.multiplyLeft(homogeneous);

		viewSpacePoints.emplace_back(
			transformed[0],
			transformed[1],
			transformed[2]
		);
	}

	return viewSpacePoints;
}

std::vector<Edge> ProjectionAction::determineVisibleEdges(
	const std::vector<Point> &viewSpacePoints,
	const std::vector<Edge> &worldEdges,
	const std::vector<Face> &worldFaces,
	const std::vector<double> &viewDirection) const
{
	if (worldFaces.empty())
		return worldEdges;

	auto planeMatrix = buildPlaneMatrix(viewSpacePoints, worldFaces);

	std::vector<bool> visibleFaces(worldFaces.size(), false);

	for (size_t i = 0; i < worldFaces.size(); ++i)
	{
		double visibility = 0.0;

		for (size_t j = 0; j < viewDirection.size() && j < planeMatrix.size(); ++j)
			if (i < planeMatrix[j].size())
				visibility += viewDirection[j] * planeMatrix[j][i];

		visibleFaces[i] = (visibility < 0);
	}

	std::vector<bool> edgeVisibility(worldEdges.size(), false);

	for (size_t faceIdx = 0; faceIdx < worldFaces.size(); ++faceIdx)
	{
		if (!visibleFaces[faceIdx])
			continue;

		const auto &face = worldFaces[faceIdx];
		const auto &vertexIndices = face.getVertexIndices();

		for (size_t i = 0; i < vertexIndices.size(); ++i)
		{
			size_t nextIdx = (i + 1) % vertexIndices.size();
			size_t v1 = vertexIndices[i];
			size_t v2 = vertexIndices[nextIdx];

			for (size_t edgeIdx = 0; edgeIdx < worldEdges.size(); ++edgeIdx)
			{
				const auto &edge = worldEdges[edgeIdx];
				if ((edge.getFirst() == v1 && edge.getSecond() == v2) ||
					(edge.getFirst() == v2 && edge.getSecond() == v1))
				{
					edgeVisibility[edgeIdx] = true;
					break;
				}
			}
		}
	}

	std::vector<Edge> visibleEdges;
	for (size_t i = 0; i < worldEdges.size(); ++i)
	{
		if (edgeVisibility[i])
		{
			visibleEdges.push_back(worldEdges[i]);
		}
	}

	return visibleEdges;
}

std::vector<Point2D> ProjectionAction::projectToScreenSpace(
	const std::vector<Point> &viewSpacePoints,
	const SquareMatrix<double> &projectionMatrix) const
{
	std::vector<Point2D> screenPoints;
	screenPoints.reserve(viewSpacePoints.size());

	for (const auto &point : viewSpacePoints)
	{
		std::vector<double> viewCoords = {
			point.getX(),
			point.getY(),
			point.getZ()
		};

		auto projected = projectionMatrix * viewCoords;

		screenPoints.emplace_back(projected[0], projected[1]);
	}

	return screenPoints;
}

Point ProjectionAction::calculateCentroid(const std::vector<Point> &points) const
{
	if (points.empty())
		return {0, 0, 0};

	double sumX = 0.0, sumY = 0.0, sumZ = 0.0;

	for (const auto &point : points)
	{
		sumX += point.getX();
		sumY += point.getY();
		sumZ += point.getZ();
	}

	auto count = static_cast<double>(points.size());
	return {sumX / count, sumY / count, sumZ / count};
}

std::vector<std::vector<double>> ProjectionAction::buildPlaneMatrix(
	const std::vector<Point> &points,
	const std::vector<Face> &faces) const
{
	if (faces.empty())
		return {};

	Point centroid = calculateCentroid(points);
	size_t numFaces = faces.size();

	std::vector<std::vector<double>> planeMatrix(4, std::vector<double>(numFaces, 0.0));

	for (size_t i = 0; i < numFaces; ++i)
	{
		const auto &face = faces[i];
		const auto &indices = face.getVertexIndices();

		if (indices.size() < 3)
			throw std::runtime_error("У грани должно быть не менее трех вершин!");

		const Point &p0 = points[indices[0]];
		const Point &p1 = points[indices[1]];
		const Point &p2 = points[indices[2]];

		double u1 = p1.getX() - p0.getX();
		double u2 = p1.getY() - p0.getY();
		double u3 = p1.getZ() - p0.getZ();

		double v1 = p2.getX() - p0.getX();
		double v2 = p2.getY() - p0.getY();
		double v3 = p2.getZ() - p0.getZ();

		double A = u2 * v3 - u3 * v2;
		double B = u3 * v1 - u1 * v3;
		double C = u1 * v2 - u2 * v1;
		double D = -(A * p0.getX() + B * p0.getY() + C * p0.getZ());

		planeMatrix[0][i] = A;
		planeMatrix[1][i] = B;
		planeMatrix[2][i] = C;
		planeMatrix[3][i] = D;

		double centroidTest = A * centroid.getX() +
			B * centroid.getY() +
			C * centroid.getZ() + D;

		if (centroidTest < 0)
		{
			planeMatrix[0][i] = -A;
			planeMatrix[1][i] = -B;
			planeMatrix[2][i] = -C;
			planeMatrix[3][i] = -D;
		}
	}

	return planeMatrix;
}
