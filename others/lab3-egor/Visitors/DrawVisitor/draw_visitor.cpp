#include "draw_visitor.h"

#include <utility>
#include "camera.h"
#include "carcass_model.h"
#include "math_utils.h"
#include "projection_action.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<Camera> camera)
	: drawer(std::move(drawer)), camera(std::move(camera))
{}

void DrawVisitor::visit(CarcassModel &model)
{
	auto modelData = model.implementor;

	auto modelMatrix = model.getPositionMatrix();
	auto viewMatrix = camera->getViewMatrix();
	auto projectionMatrix = camera->getProjectionMatrix();

	SquareMatrix<double> context = createIdentityMatrix(4);
	SquareMatrix<double> mvMatrix = viewMatrix * context * modelMatrix;

	std::vector<double> viewDirection = {0.0, 0.0, 1.0, 0.0};

	ProjectionAction projection;
	auto projectedData = projection.project(
		modelData->getPoints(),
		modelData->getEdges(),
		modelData->getFaces(),
		mvMatrix,
		projectionMatrix,
		viewDirection
	);


	for (const auto &edge : projectedData.getVisibleEdges())
	{
		const Point2D &p1 = projectedData.getScreenPoints()[edge.getFirst()];
		const Point2D &p2 = projectedData.getScreenPoints()[edge.getSecond()];
		drawer->drawLine(p1, p2);
	}
}

void DrawVisitor::visit(Camera &camera)
{
	(void)camera;
}