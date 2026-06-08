#ifndef DATA_SOURCE_CREATOR_H
#define DATA_SOURCE_CREATOR_H

#include <memory>
#include "concepts.h"
#include "model_data_source.h"

class DataSourceCreator
{
public:
	DataSourceCreator() = default;
	virtual ~DataSourceCreator() = default;

	[[nodiscard]] virtual std::shared_ptr<ModelDataSource> create(std::string filename) const = 0;
};

#endif //DATA_SOURCE_CREATOR_H
