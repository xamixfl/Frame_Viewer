#ifndef FACADE_H
#define FACADE_H

#include "../solution/SolutionDraw.h"
#include "../solution/SolutionLoader.h"
#include "../solution/SolutionScene.h"
#include "../solution/SolutionTransform.h"

class BaseCommand;

class Facade
{
    friend class BaseCommand;
public:
    Facade();
    Facade(SolutionDraw d, SolutionLoader l, SolutionTransform t, SolutionScene s);

    void execute(BaseCommand& command);

protected:
    std::shared_ptr<SolutionDraw> SolDraw;
    std::shared_ptr<SolutionLoader> SolLoader;
    std::shared_ptr<SolutionTransform> SolTransform;
    std::shared_ptr<SolutionScene> SolScene;
};

#endif // FACADE_H
