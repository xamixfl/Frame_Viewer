#include "scene_command.h"
#include "draw_manager.h"

RenderSceneCommand::RenderSceneCommand(std::shared_ptr<DrawManager> &manager)
: call(manager, &DrawManager::drawScene)
{}

void RenderSceneCommand::execute()
{
	((*call.first).*call.second)();
}

