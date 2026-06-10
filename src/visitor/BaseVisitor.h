#ifndef BASEVISITOR_H
#define BASEVISITOR_H

class BaseModelImpl;
class BaseCameraImpl;
class BaseLightImpl;

class BaseVisitor {
public:
    virtual ~BaseVisitor() = default;

    virtual void visit(BaseModelImpl& impl) noexcept = 0;
    virtual void visit(BaseCameraImpl& impl) noexcept = 0;
    virtual void visit(BaseLightImpl& impl) noexcept = 0; 
};

#endif 
