#include "transform_action.h"
#include "math_utils.h"

TransformAction::TransformAction(std::shared_ptr<TransformAction> transformation)
{
	move_ = transformation->move_;
	rotation_ = transformation->rotation_;
	scale_ = transformation->scale_;
}

TransformAction::TransformAction(const MoveData &move, const ScaleData &scale, const RotationData &rotation)
{
	move_ = move;
	rotation_ = rotation;
	scale_ = scale;
}

TransformAction TransformAction::operator+(const MoveData &other) const
{
	return {move_ + other, scale_, rotation_};
}

TransformAction TransformAction::operator+(const ScaleData &other) const
{
	return {move_, scale_ + other, rotation_};
}

TransformAction TransformAction::operator+(const RotationData &other) const
{
	return {move_, scale_, rotation_ + other};
}

TransformAction &TransformAction::operator+=(const MoveData &other)
{
	move_ += other;
	return *this;
}

TransformAction &TransformAction::operator+=(const ScaleData &other)
{
	scale_ += other;
	return *this;
}

TransformAction &TransformAction::operator+=(const RotationData &other)
{
	rotation_ += other;
	return *this;
}

TransformAction TransformAction::operator+(const TransformAction &other) const
{
	return {move_ + other.move_, scale_ + other.scale_, rotation_ + other.rotation_};
}

TransformAction &TransformAction::operator+=(const TransformAction &other)
{
	move_ += other.move_;
	scale_ += other.scale_;
	rotation_ += other.rotation_;

	return *this;
}

SquareMatrix<double> TransformAction::getResultMatrix() const
{
	return getMoveMatrix() * getRotationMatrix() * getScaleMatrix();
}

SquareMatrix<double> TransformAction::getMoveMatrix() const
{
	SquareMatrix<double> model = createIdentityMatrix(4);
	return translate(model, move_.getVector());
}

SquareMatrix<double> TransformAction::getRotationMatrix() const
{
	SquareMatrix<double> model = createIdentityMatrix(4);
//	if (fabs(rotation_.x) > 1e-6)
//	{
	model = rotate(model, radians(rotation_.x), {1.0, 0.0, 0.0});
//	}
//	if (fabs(rotation_.y) > 1e-6)
//	{
	model = rotate(model, radians(rotation_.y), {0.0, 1.0, 0.0});
//	}
//	if (fabs(rotation_.z) > 1e-6)
//	{
	model = rotate(model, radians(rotation_.z), {0.0, 0.0, -1.0});
//	}
	return model;
}

SquareMatrix<double> TransformAction::getScaleMatrix() const
{
	SquareMatrix<double> model = createIdentityMatrix(4);
	return scale(model, scale_.getVector());
}

std::vector<double> TransformAction::getMoveData() const
{
	return move_.getVector();
}
std::vector<double> TransformAction::getScaleData() const
{
	return scale_.getVector();
}
std::vector<double> TransformAction::getRotateData() const
{
	return rotation_.getVector();
}