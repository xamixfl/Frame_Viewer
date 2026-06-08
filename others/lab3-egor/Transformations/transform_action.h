#ifndef TRANSFORM_ACTION_H
#define TRANSFORM_ACTION_H

#include <memory>
#include "point.h"
#include "square_matrix.h"
#include "transformation_data.h"

class TransformAction
{
public:
	TransformAction() = default;

	explicit TransformAction(std::shared_ptr<TransformAction> transformation);

	TransformAction(const MoveData &move, const ScaleData &scale, const RotationData &rotation);

	TransformAction operator+(const MoveData& other) const;
	TransformAction operator+(const ScaleData& other) const;
	TransformAction operator+(const RotationData& other) const;

	TransformAction& operator+=(const MoveData& other);
	TransformAction& operator+=(const ScaleData& other);
	TransformAction& operator+=(const RotationData& other);

	TransformAction operator+(const TransformAction& other) const;
	TransformAction& operator+=(const TransformAction& other);

	[[nodiscard]] SquareMatrix<double> getResultMatrix() const;

	[[nodiscard]] SquareMatrix<double> getMoveMatrix() const;
	[[nodiscard]] SquareMatrix<double> getRotationMatrix() const;
	[[nodiscard]] SquareMatrix<double> getScaleMatrix() const;

	[[nodiscard]] std::vector<double> getMoveData() const;
	[[nodiscard]] std::vector<double> getScaleData() const;
	[[nodiscard]] std::vector<double> getRotateData() const;

private:
	MoveData move_{};
	ScaleData scale_{};
	RotationData rotation_{};
};

#endif //TRANSFORM_ACTION_H
