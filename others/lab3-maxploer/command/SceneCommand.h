#ifndef SCENECOMMAND_H
#define SCENECOMMAND_H

#include "BaseCommand.h"

class SceneCommand : public BaseCommand {};

class SceneClearCommand : public SceneCommand
{
public:
    SceneClearCommand() = default;
    ~SceneClearCommand() = default;

    void execute() override;
};

#endif // SCENECOMMAND_H
