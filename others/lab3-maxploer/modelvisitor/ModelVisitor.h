#ifndef MODELVISITOR_H
#define MODELVISITOR_H

#include "../visitor/AbstractVisitor.h"

class ModelVisitor : public AbstractVisitor
{
protected:
    double x, y, z;
};

#endif // MODELVISITOR_H
