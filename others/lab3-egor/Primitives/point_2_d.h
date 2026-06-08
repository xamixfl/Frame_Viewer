#ifndef POINT_2_D_H
#define POINT_2_D_H


class Point2D
{
public:
	Point2D()
		: x(0.0), y(0.0)
	{}
	Point2D(double x, double y)
		: x(x), y(y)
	{}

	[[nodiscard]] double getX() const
	{ return x; }
	[[nodiscard]] double getY() const
	{ return y; }

	void setX(double newX)
	{ x = newX; }
	void setY(double newY)
	{ y = newY; }

	Point2D operator+(const Point2D &other) const
	{
		return {x + other.x, y + other.y};
	}

	Point2D operator-(const Point2D &other) const
	{
		return {x - other.x, y - other.y};
	}

	Point2D operator*(double scalar) const
	{
		return {x * scalar, y * scalar};
	}

private:
	double x, y;
};


#endif //POINT_2_D_H
