//#ifndef DRAW_VISITOR_H
//#define DRAW_VISITOR_H
//
//#include "base_visitor.h"
//#include "base_drawer.h"
//#include "square_matrix.h"
//
//class DrawVisitor: public BaseVisitor
//{
//public:
//	DrawVisitor() = delete;
//	DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<Camera> camera);
//
//	void visit(CarcassModel &model) override;
//	void visit(Camera &camera) override;
//
//private:
//	std::shared_ptr<BaseDrawer> drawer;
//	std::shared_ptr<Camera> camera;
//};
//
//
//#endif //DRAW_VISITOR_H
#ifndef DRAW_VISITOR_H
#define DRAW_VISITOR_H

#include <vector>
#include <memory>
#include "base_visitor.h"
#include "base_drawer.h"
#include "square_matrix.h"
#include "carcass_model_implementor.h"
#include "face.h"
#include "edge.h"
#include "point.h"
#include "body.h"
#include "camera.h"

class DrawVisitor: public BaseVisitor
{
public:
	DrawVisitor() = delete;
	DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<Camera> camera);

	void visit(CarcassModel &model) override;
	void visit(Camera &camera) override;

private:
	std::shared_ptr<BaseDrawer> drawer;
	std::shared_ptr<Camera> camera;
};

#endif //DRAW_VISITOR_H