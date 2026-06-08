#include "model_data_source.h"

Point ModelDataSource::findCenter()
{
	std::vector<Point> points = readPoints();
	if (points.empty())
		return {};

	double minX = points[0].getX(), minY = points[0].getY(), minZ = points[0].getZ();
	double maxX = points[0].getX(), maxY = points[0].getY(), maxZ = points[0].getZ();

	for (auto &p : points)
	{
		if (minX > p.getX())
			minX = p.getX();
		if (minY > p.getY())
			minY = p.getY();
		if (minZ > p.getZ())
			minZ = p.getZ();
		if (maxX < p.getX())
			maxX = p.getX();
		if (maxY < p.getY())
			maxY = p.getY();
		if (maxZ < p.getZ())
			maxZ = p.getZ();
	}

	return Point((minX + maxX) / 2, (minY + maxY) / 2, (maxZ + minZ) / 2);
}
