#include "list_carcass_model_director.h"
#include "list_carcass_model_builder.h"

ListCarcassModelDirector::ListCarcassModelDirector(std::shared_ptr<ModelDataSource> dataSource)
{
	builder = std::make_shared<ListCarcassModelBuilder>(dataSource);
}
