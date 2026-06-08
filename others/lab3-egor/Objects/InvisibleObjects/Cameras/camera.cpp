#include <algorithm>
#include <iostream>
#include "camera.h"
#include "math_utils.h"

Camera::Camera(const std::vector<double> &position, const std::vector<double> &up, double yaw, double pitch)
{
	this->position = position;
	forward = {0, 0, -1};
	worldUp = up;
	Yaw = yaw;
	Pitch = pitch;

	*scenePosition += RotationData{Yaw, Pitch, 0};

	updateCameraVectors();
}

void Camera::accept(std::shared_ptr<BaseVisitor> visitor)
{
	visitor->visit(*this);
}

SquareMatrix<double> Camera::getViewMatrix()
{
	auto pos = scenePosition->getMoveMatrix() * position;
	auto gyro = scenePosition->getRotateData();

	Yaw = std::clamp(gyro[0], MIN_YAW, MAX_YAW);
	Pitch = std::clamp(gyro[1], MIN_PITCH, MAX_PITCH);

	updateCameraVectors();

	std::vector<double> eye(3);
	for (int i = 0; i < 3; i++)
		eye[i] = pos[i] + forward[i];

	return lookAt(pos, eye, up);
}

SquareMatrix<double> Camera::getProjectionMatrix()
{
	return perspective(0.75, aspect, zNear, zFar);
}

void Camera::updateCameraVectors()
{
	std::vector<double> front = {cos(radians(Yaw)) * cos(radians(Pitch)),
								 sin(radians(Pitch)),
								 sin(radians(Yaw)) * cos(radians(Pitch))};

	forward = normalize(front);
	right = normalize(cross(forward, worldUp));
	up = normalize(cross(right, forward));
}

std::vector<double> Camera::getPosition() const
{
	return position;
}
