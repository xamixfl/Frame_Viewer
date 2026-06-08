#include "object_command.h"
#include <utility>
#include "manager_solution.h"
#include "scene_manager.h"
#include "load_manager.h"
#include "transform_manager.h"


DeleteObjectCommand::DeleteObjectCommand(std::shared_ptr<SceneManager> scene_manager, size_t id)
	: call(scene_manager, &SceneManager::removeObject), model_id_(id)
{}

void DeleteObjectCommand::execute()
{
	((*call.first).*call.second)(model_id_);
}

LoadModelCommand::LoadModelCommand(std::shared_ptr<LoadManager> load_manager,
								   std::shared_ptr<SceneManager> scene_manager,
								   std::string file_name)

	: loadCall(load_manager, &LoadManager::loadModelFromFile),
	  addCall(scene_manager, &SceneManager::addObject),
	  file_name(std::move(file_name))
{}

void LoadModelCommand::execute()
{
	auto model = ((*loadCall.first).*loadCall.second)(file_name);
	model_id_ = ((*addCall.first).*addCall.second)(model);
}

int LoadModelCommand::getObjectId() const
{
	return model_id_;
}

RotateObjectCommand::RotateObjectCommand(std::shared_ptr<SceneManager> sceneManager,
										 std::shared_ptr<TransformManager> transformManager,
										 size_t id,
										 double ox,
										 double oy,
										 double oz)
	: getCall(sceneManager, &SceneManager::getObject),
	  rotateCall(transformManager, &TransformManager::rotateObject),
	  model_id_(id),
	  ox_(ox), oy_(oy), oz_(oz)
{}

void RotateObjectCommand::execute()
{
	auto object = ((*getCall.first).*getCall.second)(model_id_);
	((*rotateCall.first).*rotateCall.second)(object, ox_, oy_, oz_);
}

ScaleObjectCommand::ScaleObjectCommand(std::shared_ptr<SceneManager> sceneManager,
									   std::shared_ptr<TransformManager> transformManager,
									   size_t id,
									   double kx,
									   double ky,
									   double kz)
	: getCall(sceneManager, &SceneManager::getObject),
	  scaleCall(transformManager, &TransformManager::scaleObject),
	  model_id_(id),
	  kx_(kx), ky_(ky), kz_(kz)
{}

void ScaleObjectCommand::execute()
{
	auto object = ((*getCall.first).*getCall.second)(model_id_);
	((*scaleCall.first).*scaleCall.second)(object, kx_, ky_, kz_);
}

MoveObjectCommand::MoveObjectCommand(std::shared_ptr<SceneManager> sceneManager,
									 std::shared_ptr<TransformManager> transformManager,
									 size_t id,
									 double dx,
									 double dy,
									 double dz)
	: getCall(sceneManager, &SceneManager::getObject),
	  moveCall(transformManager, &TransformManager::moveObject),
	  model_id_(id),
	  dx_(dx), dy_(dy), dz_(dz)
{}

void MoveObjectCommand::execute()
{
	auto object = ((*getCall.first).*getCall.second)(model_id_);
	((*moveCall.first).*moveCall.second)(object, dx_, dy_, dz_);
}

CompositeObjectCommand::CompositeObjectCommand(std::shared_ptr<SceneManager> sceneManager, std::vector<int> ids)
	: compositeCall(sceneManager, &SceneManager::makeComposite),
	  model_ids_(std::move(ids))
{}

void CompositeObjectCommand::execute()
{
	composite_id_ = ((*compositeCall.first).*compositeCall.second)(model_ids_);
}

int CompositeObjectCommand::getCompositeId() const
{
	return composite_id_;
}

