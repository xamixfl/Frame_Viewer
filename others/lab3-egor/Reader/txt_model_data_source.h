#ifndef TXT_MODEL_DATA_SOURCE_H
#define TXT_MODEL_DATA_SOURCE_H

#include "model_data_source.h"
#include <fstream>

class TxtModelDataSource: public ModelDataSource
{
public:
	TxtModelDataSource() = default;
	explicit TxtModelDataSource(std::string filename);
	~TxtModelDataSource() override;

	void open() override;
	void close() override;
	[[nodiscard]] bool isOpen() const override;

	std::vector<Point> readPoints() override;
	std::vector<Edge> readEdges() override;
	std::vector<Face> readFaces() override;

private:
	std::string fileName;
	std::ifstream file;
};


#endif //TXT_MODEL_DATA_SOURCE_H
