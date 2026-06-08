#ifndef OBJECT_COMMAND_H
#define OBJECT_COMMAND_H

#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include "command.h"
#include "base_object.h"

class SceneManager;
class LoadManager;
class TransformManager;

class ObjectCommand: public Command
{
public:
	ObjectCommand() = default;
	~ObjectCommand() override = default;
};

class DeleteObjectCommand: public ObjectCommand
{
	using Action = bool (SceneManager::*)(int);
	using Pair = std::pair<std::shared_ptr<SceneManager>, Action>;

public:
	DeleteObjectCommand(std::shared_ptr<SceneManager> scene_manager, size_t id);
	void execute() override;

private:
	size_t model_id_;
	Pair call;
};

class LoadModelCommand: public ObjectCommand
{
	using LoadAction = std::shared_ptr<BaseObject>(LoadManager::*)(const std::string &);
	using AddAction = int (SceneManager::*)(std::shared_ptr<BaseObject>);
	using LoadPair = std::pair<std::shared_ptr<LoadManager>, LoadAction>;
	using AddPair = std::pair<std::shared_ptr<SceneManager>, AddAction>;

public:
	explicit LoadModelCommand(std::shared_ptr<LoadManager> load_manager,
							  std::shared_ptr<SceneManager> scene_manager,
							  std::string file_name);
	void execute() override;
	int getObjectId() const;
private:
	int model_id_;
	LoadPair loadCall;
	AddPair addCall;
	std::string file_name;
};

class RotateObjectCommand: public ObjectCommand
{
	using GetAction = std::shared_ptr<BaseObject>(SceneManager::*)(int);
	using RotateAction = void (TransformManager::*)(const std::shared_ptr<BaseObject> &, double, double, double);
	using GetPair = std::pair<std::shared_ptr<SceneManager>, GetAction>;
	using RotatePair = std::pair<std::shared_ptr<TransformManager>, RotateAction>;

public:
	RotateObjectCommand(std::shared_ptr<SceneManager> sceneManager,
						std::shared_ptr<TransformManager> transformManager,
						size_t id,
						double ox,
						double oy,
						double oz);
	void execute() override;

private:
	GetPair getCall;
	RotatePair rotateCall;
	size_t model_id_;
	double ox_, oy_, oz_;
};

class ScaleObjectCommand: public ObjectCommand
{
	using ScaleAction = void (TransformManager::*)(const std::shared_ptr<BaseObject> &, double, double, double);
	using GetAction = std::shared_ptr<BaseObject>(SceneManager::*)(int);
	using ScalePair = std::pair<std::shared_ptr<TransformManager>, ScaleAction>;
	using GetPair = std::pair<std::shared_ptr<SceneManager>, GetAction>;
public:
	explicit ScaleObjectCommand(std::shared_ptr<SceneManager> sceneManager,
								std::shared_ptr<TransformManager> transformManager,
								size_t id,
								double kx,
								double ky,
								double kz);
	void execute() override;

private:
	GetPair getCall;
	ScalePair scaleCall;
	size_t model_id_;
	double kx_, ky_, kz_;
};

class MoveObjectCommand: public ObjectCommand
{
	using MoveAction = void (TransformManager::*)(const std::shared_ptr<BaseObject> &, double, double, double);
	using GetAction = std::shared_ptr<BaseObject>(SceneManager::*)(int);
	using MovePair = std::pair<std::shared_ptr<TransformManager>, MoveAction>;
	using GetPair = std::pair<std::shared_ptr<SceneManager>, GetAction>;

public:
	explicit MoveObjectCommand(std::shared_ptr<SceneManager> sceneManager,
							   std::shared_ptr<TransformManager> transformManager,
							   size_t id,
							   double dx,
							   double dy,
							   double dz);
	void execute() override;

private:
	MovePair moveCall;
	GetPair getCall;
	size_t model_id_;
	double dx_, dy_, dz_;
};

class CompositeObjectCommand: public ObjectCommand
{
	using CreateCompositeAction = int (SceneManager::*)(const std::vector<int> &);
	using Pair = std::pair<std::shared_ptr<SceneManager>, CreateCompositeAction>;
public:
	explicit CompositeObjectCommand(std::shared_ptr<SceneManager> sceneManager, std::vector<int> ids);
	void execute() override;
	int getCompositeId() const;
private:
	Pair compositeCall;
	std::vector<int> model_ids_;
	int composite_id_;
};

#endif //OBJECT_COMMAND_H
