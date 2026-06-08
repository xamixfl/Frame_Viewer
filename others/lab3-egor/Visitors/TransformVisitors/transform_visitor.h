#ifndef TRANSFORM_VISITOR_H
#define TRANSFORM_VISITOR_H

#include "base_visitor.h"
#include "transform_action.h"

class TransformVisitor: public BaseVisitor
{
public:
	TransformVisitor() = delete;
	explicit TransformVisitor(std::shared_ptr<TransformAction> action);
	TransformVisitor(const MoveData &move, const ScaleData &scale, const RotationData &rotation);
	~TransformVisitor() = default;

	void visit(CarcassModel &model) override;
	void visit(Camera &camera) override;

private:
	std::shared_ptr<TransformAction> t_action;
};


#endif //TRANSFORM_VISITOR_H
