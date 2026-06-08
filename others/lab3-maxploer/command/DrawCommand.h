#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include "BaseCommand.h"
#include <QGraphicsScene>
#include <QGraphicsView>

class DrawCommand : public BaseCommand {};

class Draw : public DrawCommand
{
public:
    Draw() = default;
    ~Draw() = default;

    void execute() override;
};


#endif // DRAWCOMMAND_H
