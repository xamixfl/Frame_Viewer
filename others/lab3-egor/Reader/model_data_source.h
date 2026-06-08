#ifndef MODEL_DATA_SOURCE_H
#define MODEL_DATA_SOURCE_H

#include "data_source.h"
#include "edge.h"
#include "point.h"
#include "face.h"
#include <vector>


class ModelDataSource: public DataSource
{
public:
	ModelDataSource() = default;
	~ModelDataSource() override = default;

	virtual void open() = 0;
	virtual void close() = 0;
	[[nodiscard]] virtual bool isOpen() const = 0;

	virtual std::vector<Point> readPoints() = 0;
	virtual std::vector<Edge> readEdges() = 0;
	virtual std::vector<Face> readFaces() = 0;
	virtual Point findCenter();
};

#endif //MODEL_DATA_SOURCE_H
