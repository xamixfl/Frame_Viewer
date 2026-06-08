#ifndef TRANSFORMATION_DATA_H
#define TRANSFORMATION_DATA_H


#include <vector>
class TransformationData
{
};

class MoveData: public TransformationData
{
public:
	double x{}, y{}, z{};
	MoveData() = default;
	MoveData(double x, double y, double z)
		: x(x), y(y), z(z)
	{};

	explicit MoveData(const std::vector<double> &vec)
		: x(vec[0]), y(vec[1]), z(vec[2])
	{};

	virtual ~MoveData() = default;

	MoveData operator+(const MoveData &other) const;
	MoveData &operator+=(const MoveData &other);


	[[nodiscard]] std::vector<double> getVector() const
	{
		return {x, y, z};
	};
};

class ScaleData: public TransformationData
{
public:
	double x{1}, y{1}, z{1};
	ScaleData()
	{
		x = y = z = 1;
	};
	ScaleData(double x, double y, double z)
		: x(x), y(y), z(z)
	{};
	explicit ScaleData(const std::vector<double> &vec)
		: x(vec[0]), y(vec[1]), z(vec[2])
	{};
	virtual ~ScaleData() = default;

	ScaleData operator+(const ScaleData &other) const;
	ScaleData &operator+=(const ScaleData &other);

	[[nodiscard]] std::vector<double> getVector() const
	{
		return {x, y, z};
	};
};

class RotationData: public TransformationData
{
public:
	double x{}, y{}, z{};
	RotationData() = default;
	RotationData(double x, double y, double z)
		: x(x), y(y), z(z)
	{};
	RotationData(const std::vector<double> &vec)
		: x(vec[0]), y(vec[1]), z(vec[2])
	{};
	virtual ~RotationData() = default;

	RotationData operator+(const RotationData &other) const;
	RotationData &operator+=(const RotationData &other);

	[[nodiscard]] std::vector<double> getVector() const
	{
		return {x, y, z};
	};
};


#endif //TRANSFORMATION_DATA_H
