#ifndef BASE_VISITOR_H__
#define BASE_VISITOR_H__

class ModelImpl;
class CameraImpl;

class BaseVisitor
{
public:
    BaseVisitor() = default;
    virtual ~BaseVisitor() = 0;

    virtual void visit(ModelImpl &obj) = 0;
    virtual void visit(CameraImpl &obj) = 0;
};

#endif