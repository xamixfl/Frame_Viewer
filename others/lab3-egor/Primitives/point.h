#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point() = default;
	Point(double x, double y, double z);
	explicit Point(const Point &p) = default;
	Point(Point &&p) noexcept = default;

	Point &operator=(const Point &p) = default;
	Point &operator=(Point &&p) noexcept = default;

	Point operator-(const Point &p) const;
	~Point() = default;

	[[nodiscard]] double getX() const;
	[[nodiscard]] double getY() const;
	[[nodiscard]] double getZ() const;

	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void set(double x, double y, double z);
	void set(const Point &p);

	bool operator==(const Point &p) const;

	Point &normalize();
	Point cross(const Point &other) const;

private:
	double x = 0, y = 0, z = 0;
};

#endif //POINT_H
