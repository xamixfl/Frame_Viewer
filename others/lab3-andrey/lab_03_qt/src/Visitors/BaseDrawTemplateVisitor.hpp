#ifndef BASEVISITOR_HPP
#define BASEVISITOR_HPP

class AbstractFigureLP;

class BaseDrawTemplateVisitor
{
public:
    BaseDrawTemplateVisitor() = default;
    virtual ~BaseDrawTemplateVisitor() = default;

    virtual void visit(const AbstractFigureLP &figure) const = 0;
};

#endif //BASEVISITOR_HPP
