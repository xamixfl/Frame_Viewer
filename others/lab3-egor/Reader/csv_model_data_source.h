#ifndef CSV_MODEL_DATA_SOURCE_H
#define CSV_MODEL_DATA_SOURCE_H

#include <memory>
#include "model_data_source.h"
#include "rapidcsv.h"

class CsvModelDataSource: public ModelDataSource
{
public:
	CsvModelDataSource() = default;
	explicit CsvModelDataSource(std::string filename);
	~CsvModelDataSource() override;

	void open() override;
	void close() override;
	[[nodiscard]] bool isOpen() const override;

	std::vector<Point> readPoints() override;
	std::vector<Edge> readEdges() override;
	std::vector<Face> readFaces() override;

private:
	std::string fileName;
	std::unique_ptr<rapidcsv::Document> doc;
};


#endif //CSV_MODEL_DATA_SOURCE_H
