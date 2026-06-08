#ifndef SCENE_COMMAND_H
#define SCENE_COMMAND_H

#include "command.h"
#include "draw_manager.h"

class SceneCommand: public Command
{
};

class RenderSceneCommand: public SceneCommand
{
	using Action = void (DrawManager::*)();
	using Pair = std::pair<std::shared_ptr<DrawManager>, Action>;
public:
	explicit RenderSceneCommand(std::shared_ptr<DrawManager> &manager);
	void execute() override;
private:
	Pair call;
};


#endif //SCENE_COMMAND_H
