#include <cmath>
#include "point.h"

Point::Point(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double Point::getX() const
{
	return this->x;
}

double Point::getY() const
{
	return this->y;
}

double Point::getZ() const
{
	return this->z;
}

void Point::setX(double x)
{
	this->x = x;
}

void Point::setY(double y)
{
	this->y = y;
}

void Point::setZ(double z)
{
	this->z = z;
}

void Point::set(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::set(const Point &p)
{
	this->x = p.getX();
	this->y = p.getY();
	this->z = p.getZ();
}

bool Point::operator==(const Point &p) const
{
	return this->x == p.getX() && this->y == p.getY() && this->z == p.getZ();
}

Point &Point::normalize()
{
	double length = std::sqrt(x * x + y * y + z * z);
	if (length > 0)
	{
		x /= length;
		y /= length;
		z /= length;
	}
	return *this;
}

Point Point::cross(const Point &other) const
{
	return {
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	};
}

Point Point::operator-(const Point &p) const
{
	return {x - p.x, y - p.y, z - p.z};
}
