#include "transform_visitor.h"
#include "carcass_model.h"
#include "camera.h"

#include <utility>

TransformVisitor::TransformVisitor(std::shared_ptr<TransformAction> action)
{
	t_action = std::move(action);
}

TransformVisitor::TransformVisitor(const MoveData &move, const ScaleData &scale, const RotationData &rotation)
	: t_action(std::make_shared<TransformAction>(move, scale, rotation))
{}

void TransformVisitor::visit(CarcassModel &model)
{
	auto currentTransform = model.getScenePosition();
	*currentTransform += *t_action;
}

void TransformVisitor::visit(Camera &camera)
{
	auto currentTransform = camera.getScenePosition();
	*currentTransform += *t_action;
}
