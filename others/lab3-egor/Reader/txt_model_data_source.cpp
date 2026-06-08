#include <iostream>
#include <sstream>
#include "txt_model_data_source.h"
#include "model_exception.h"

TxtModelDataSource::TxtModelDataSource(std::string filename)
{
	fileName = filename;
}

TxtModelDataSource::~TxtModelDataSource()
{
	if (isOpen())
		close();
}

void TxtModelDataSource::open()
{
	if (file.is_open())
		return;
	file.open(fileName);
	if (!file)
		throw FileOpenException(__FILE__, __LINE__, __func__, "Unable to open file");
}

void TxtModelDataSource::close()
{
	if (!file.is_open())
		return;
	file.close();
}

bool TxtModelDataSource::isOpen() const
{
	return file.is_open();
}

std::vector<Point> TxtModelDataSource::readPoints()
{
	if (!isOpen())
		return {};

	std::vector<Point> points;
	file.clear();
	file.seekg(0);

	int size = 0;
	file >> size;

	points.resize(size);
	double x, y, z;
	for (int i = 0; i < size; ++i)
	{
		file >> x >> y >> z;
		if (file.fail())
			throw FileBadFormatException(__FILE__, __LINE__, __func__, "Wrong format of points");

		points[i].setX(x);
		points[i].setY(y);
		points[i].setZ(z);
	}

	return points;
}

std::vector<Edge> TxtModelDataSource::readEdges()
{
	if (!isOpen())
		return {};

	file.clear();
	file.seekg(0);

	int pointCount;
	file >> pointCount;
	double x, y, z;
	for (int i = 0; i < pointCount; ++i)
		file >> x >> y >> z;


	std::vector<Edge> edges;
	int size = 0;
	file >> size;
	edges.resize(size);
	size_t first, second;
	for (int i = 0; i < size; ++i)
	{
		file >> first >> second;
		if (file.fail())
			throw FileBadFormatException(__FILE__, __LINE__, __func__, "Wrong format of edges");

		edges[i].setFirst(first - 1);
		edges[i].setSecond(second - 1);
	}

	return edges;
}

std::vector<Face> TxtModelDataSource::readFaces()
{
	if (!isOpen())
		return {};

	file.clear();
	file.seekg(0);

	int pointCount;
	file >> pointCount;
	double x, y, z;
	for (int i = 0; i < pointCount; ++i)
		file >> x >> y >> z;

	int edgeCount;
	file >> edgeCount;
	size_t first, second;
	for (int i = 0; i < edgeCount; ++i)
		file >> first >> second;

	std::vector<Face> faces;
	int faceCount = 0;

	if (file >> faceCount)
	{
		std::string line;
		std::getline(file, line);

		for (int i = 0; i < faceCount; ++i)
		{
			if (!std::getline(file, line))
				break;

			std::istringstream iss(line);
			std::vector<size_t> indices;
			size_t index;

			while (iss >> index)
				indices.push_back(index - 1);

			if (!indices.empty())
				faces.emplace_back(indices);
		}
	}

	return faces;

}

