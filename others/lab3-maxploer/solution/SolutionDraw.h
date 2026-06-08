#ifndef SOLUTIONDRAW_H
#define SOLUTIONDRAW_H

#include "BaseSolution.h"
#include "../draw/DrawVisitor.h"
#include "../object/AbstractObject.h"
#include "../object/camera/Camera.h"

class SolutionDraw : public BaseSolution
{
public:
    SolutionDraw();
    explicit SolutionDraw(std::shared_ptr<DrawVisitor> visitor);
    ~SolutionDraw() = default;

    void set_visitor(std::shared_ptr<DrawVisitor> visitor);
    void accept(std::shared_ptr<AbstractObject> obj);
    void set_camera(std::shared_ptr<Camera> camera);

protected:
    std::shared_ptr<DrawVisitor> visitor;
};

#endif // SOLUTIONDRAW_H
