#ifndef CAMERA_H
#define CAMERA_H

#include "draw_visitor.h"
#include "transform_visitor.h"
#include "invisible_object.h"

constexpr const double YAW = -90.0;
constexpr const double PITCH =  0.0;
constexpr const double MAX_YAW = 360.0;
constexpr const double MIN_YAW = -360.0;

constexpr const double MAX_PITCH = 89.0;
constexpr const double MIN_PITCH = -89.0;

constexpr const double MAX_ROLL = 180.0;
constexpr const double MIN_ROLL = -180.0;

class Camera: public InvisibleObject
{
	friend class DrawVisitor;
	friend class TransformVisitor;
public:
	explicit Camera(const std::vector<double> &position, const std::vector<double> &up={0.0, 1.0, 0.0}, double yaw=YAW, double pitch=PITCH);

	~Camera() override = default;

	virtual void accept(std::shared_ptr<BaseVisitor> visitor);
	std::vector<double> getPosition() const;

protected:
	SquareMatrix<double> getViewMatrix();
	SquareMatrix<double> getProjectionMatrix();

	std::vector<double> position{};
	std::vector<double> forward{};
	std::vector<double> up{};
	std::vector<double> right{};
	std::vector<double> worldUp{};

	double Yaw;
	double Pitch;
	double aspect = 1.0;
	double zNear = 0.1;
	double zFar = 10000.0;
	void updateCameraVectors();
};


#endif //CAMERA_H
