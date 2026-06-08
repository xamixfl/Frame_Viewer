#ifndef BASETRANSFORMVISITOR_HPP
#define BASETRANSFORMVISITOR_HPP

class AbstractFigureLP;
class BaseCameraPTUImpl;

class BaseTransformVisitor
{
public:
    BaseTransformVisitor() = default;
    virtual ~BaseTransformVisitor() = default;

    virtual void visit(AbstractFigureLP &figure) {}
    virtual void visit(BaseCameraPTUImpl &camera) {}
};



#endif //BASETRANSFORMVISITOR_HPP
