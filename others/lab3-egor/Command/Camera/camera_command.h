#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include <cstddef>
#include "command.h"
#include "point.h"
#include "camera_manager.h"

class CameraCommand: public Command
{
};

class AddCameraCommand: public CameraCommand
{
	using Action = int (CameraManager::*)(const Point &);
	using Pair = std::pair<std::shared_ptr<CameraManager>, Action>;
public:
	explicit AddCameraCommand(std::shared_ptr<CameraManager> cameraManager, const Point &position);
	void execute() override;
	int getCameraId() const;

private:
	Pair call;
	int camera_id;
	Point position_;
};

class SetCameraCommand: public CameraCommand
{
	using Action = void (CameraManager::*)(int);
	using Pair = std::pair<std::shared_ptr<CameraManager>, Action>;

public:
	explicit SetCameraCommand(std::shared_ptr<CameraManager> cameraManager, size_t id);
	void execute() override;

private:
	Pair call;
	size_t camera_id;
};

class DeleteCameraCommand: public CameraCommand
{
	using Action = bool (CameraManager::*)(int);
	using Pair = std::pair<std::shared_ptr<CameraManager>, Action>;
public:
	explicit DeleteCameraCommand(std::shared_ptr<CameraManager> cameraManager, size_t id);
	void execute() override;
private:
	Pair call;
	size_t camera_id;
};

class MoveCameraCommand: public CameraCommand
{
	using Action = void (CameraManager::*)(int, double, double, double);
	using Pair = std::pair<std::shared_ptr<CameraManager>, Action>;
public:
	explicit MoveCameraCommand(std::shared_ptr<CameraManager> cameraManager,
							   size_t id,
							   double dx,
							   double dy,
							   double dz);
	void execute() override;
private:
	Pair call;
	size_t camera_id;
	double dx, dy, dz;
};

class RotateCameraCommand:public CameraCommand
{
	using Action = void (CameraManager::*)(int, double, double);
	using Pair = std::pair<std::shared_ptr<CameraManager>, Action>;
public:
	explicit RotateCameraCommand(std::shared_ptr<CameraManager> cameraManager, size_t id, double ax, double ay);
	void execute() override;
private:
	Pair call;
	size_t camera_id;
	double ax, ay;
};

#endif //CAMERA_COMMAND_H
