#ifndef BASE_VISITOR_H
#define BASE_VISITOR_H

#include <memory>

class CarcassModel;
class Camera;

class BaseVisitor
{
public:
	BaseVisitor() = default;
	virtual void visit(CarcassModel &model) = 0;
	virtual void visit(Camera &camera) = 0;
};


#endif //BASE_VISITOR_H
