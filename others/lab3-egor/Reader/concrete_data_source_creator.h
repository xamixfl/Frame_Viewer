#ifndef CONCRETE_DATA_SOURCE_CREATOR_H
#define CONCRETE_DATA_SOURCE_CREATOR_H

#include "data_source_creator.h"
#include "model_data_source.h"
#include "txt_model_data_source.h"
#include "csv_model_data_source.h"


template<Derivative<DataSource> TDataSource>
requires NotAbstract<TDataSource>
class ConcreteDataSourceCreator: public DataSourceCreator
{
public:
	[[nodiscard]] std::shared_ptr<ModelDataSource> create(std::string fileName) const override
	{
		return std::make_shared<TDataSource>(fileName);
	}
};


#endif //CONCRETE_DATA_SOURCE_CREATOR_H
